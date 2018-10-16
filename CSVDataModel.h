#pragma once

#include <QString>

namespace eeg
{
	class ICSVDataModel
	{
	public:
		ICSVDataModel() {}
		virtual ~ICSVDataModel() {}

		void setEEGData(const Data* data) { _data = data; }

		virtual short columnCount() = 0;
		virtual QString columnName(short columnId) = 0;
		virtual QString data(short columnId) = 0;

	protected:
		const Data* _data{ nullptr };
	};
};
