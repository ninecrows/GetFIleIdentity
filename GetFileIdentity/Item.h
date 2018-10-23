#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>

namespace C9
{
	namespace Json
	{
		class Item
		{
		public:
			inline
			Item(void)
			{

			}

			inline
				virtual
				~Item(void)
			{

			}
		};

		class ItemString : public Item
		{
		private:
			std::wstring value;
				
		public:
			ItemString(const std::wstring myValue) : value(myValue)
			{
			}

			std::wstring
				getValue(void) const
			{
				return (value);
			}
		};

		class ItemNumber : public Item
		{
		private:
			double value;
						
		public:
			ItemNumber(double myValue) : value(myValue)
			{

			}

			double
				getValue(void) const
			{
				return (value);
			}
		};

		class ItemBoolean : public Item
		{
		private:
			bool value;

		public:
			ItemBoolean(bool myValue) : value(myValue)
			{

			}

			inline
			bool
				getValue(void) const
			{
				return (value);
			}
		};

		class ItemNull : public Item
		{
		public:
			ItemNull(void)
			{

			}
		};

		class ItemArray : public Item
		{
		private:
			std::vector<std::shared_ptr<Item>> value;

		public:
			ItemArray(void)
			{

			}

			ItemArray(std::vector<std::shared_ptr<Item>> values) : value(values)
			{

			}

			size_t
				size(void) const
			{
				return (value.size());
			}

			std::shared_ptr<Item> 
				getValue(size_t index)
			{
				return (value[index]);
			}

			void
				add(std::shared_ptr<Item> myValue)
			{
				value.push_back(myValue);
			}
		};

		class ItemObject : public Item
		{
		private:
			std::map<std::wstring, std::shared_ptr<Item>> value;

		public:
			ItemObject(void)
			{

			}

			ItemObject(std::map<std::wstring, std::shared_ptr<Item>> values) : value(values)
			{

			}

			size_t
				size(void) const
			{
				return (value.size());
			}

			bool
				contains(std::wstring key) const
			{
				return (value.find(key) != value.end());
			}

			std::shared_ptr<Item> 
				getValue(std::wstring key)
			{
				return (value[key]);
			}

			void
				add(const std::wstring &key,
					std::shared_ptr<Item> myValue)
			{
				value[key] = myValue;
			}
		};
	}
}