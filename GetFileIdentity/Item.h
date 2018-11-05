#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>

namespace C9
{
	namespace Json
	{
		class Value
		{
		public:
			inline
			Value(void)
			{

			}

			inline
				virtual
				~Value(void)
			{

			}
		};

		class String : public Value
		{
		private:
			std::wstring value;
				
		public:
			String(const std::wstring myValue) : value(myValue)
			{
			}

			std::wstring
				getValue(void) const
			{
				return (value);
			}
		};

		class Number : public Value
		{
		private:
			double value;
						
		public:
			Number(double myValue) : value(myValue)
			{

			}

			double
				getValue(void) const
			{
				return (value);
			}
		};

		class Boolean : public Value
		{
		private:
			bool value;

		public:
			Boolean(bool myValue) : value(myValue)
			{

			}

			inline
			bool
				getValue(void) const
			{
				return (value);
			}
		};

		class ItemNull : public Value
		{
		public:
			ItemNull(void)
			{

			}
		};

		class Array : public Value
		{
		private:
			std::vector<std::shared_ptr<Value>> value;

		public:
			Array(void)
			{

			}

			Array(std::vector<std::shared_ptr<Value>> values) : value(values)
			{

			}

			size_t
				size(void) const
			{
				return (value.size());
			}

			std::shared_ptr<Value> 
				getValue(size_t index)
			{
				return (value[index]);
			}

			void
				add(std::shared_ptr<Value> myValue)
			{
				value.push_back(myValue);
			}
		};

		class Object : public Value
		{
		private:
			std::map<std::wstring, std::shared_ptr<Value>> value;

		public:
			Object(void)
			{

			}

			Object(std::map<std::wstring, std::shared_ptr<Value>> values) : value(values)
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

			std::shared_ptr<Value> 
				getValue(std::wstring key)
			{
				return (value[key]);
			}

			void
				add(const std::wstring &key,
					std::shared_ptr<Value> myValue)
			{
				value[key] = myValue;
			}
		};
	}
}