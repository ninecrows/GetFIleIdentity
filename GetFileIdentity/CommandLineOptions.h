#pragma once

#include <string>
#include <vector>
#include <regex>
#include <map>


class CommandLineOptions
{
private:
	std::wstring m_Command;
	std::vector<std::wstring> m_Arguments;
	std::map<std::wstring, std::wstring> m_Options;
	//std::vector<std::pair<std::wstring, std::wstring>> m_Options;
	std::vector<std::wstring> m_Items;

private:
	const std::wregex m_LongOption;
	const std::wregex m_ValuedOption;

public:
	inline
		CommandLineOptions(int argc, wchar_t *argv[]) :
		m_LongOption(L"^--(.*)$"),
		m_ValuedOption(L"^([^=]+)=(.*)$")
	{
		m_Command = std::wstring(argv[0]);

		for (int ct = 1; ct < argc; ct++)
		{
			m_Arguments.push_back(argv[ct]);

			std::wsmatch match;
			if (std::regex_search(m_Arguments[ct - 1], match, m_LongOption))
			{
				std::wstring wholeSwitch(match[1]);
				std::wsmatch switchParts;
				if (std::regex_search(wholeSwitch, switchParts, m_ValuedOption))
				{
					auto thisItem = m_Options.find(switchParts[1]);
					if (thisItem != m_Options.end())
					{
						// There's already switch data associated with this tag so add more.
						(*thisItem).second += L",";
						(*thisItem).second += switchParts[2];
					}
					else
					{
						// Add a new switch with this data.
						m_Options[switchParts[1]] = switchParts[2];
					}
				}
				else
				{
					// Just the switch, no payload.
					m_Options[match[1]] = L"";
				}
			}

			// Non-switch item.
			else
			{
				m_Items.push_back(m_Arguments[ct - 1]);
			}
		}
	}

public:
	inline
		size_t
		OptionCount()
	{
		return (m_Options.size());
	}

	inline
		size_t
		ItemCount()
	{
		return (m_Items.size());
	}

	inline
		const std::wstring&
		OptionValue(const std::wstring &tag)
	{
		return(m_Options[tag]);
	}

	inline
		bool
		OptionExists(const std::wstring &tag)
	{
		return (m_Options.find(tag) != m_Options.end());
	}

	inline
		const std::wstring &
		Item(size_t itemNumber)
	{
		return (m_Items[itemNumber]);
	}

	inline
		std::vector<std::wstring>
		Items(void)
	{
		return (m_Items);
	}

	inline
		std::map<std::wstring, std::wstring>
		Options(void)
	{
		return (m_Options);
	}
};