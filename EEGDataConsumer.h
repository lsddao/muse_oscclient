#pragma once

#include "EEGData.h"

namespace eeg
{
	class IDataConsumer
	{
	public:
		IDataConsumer() {}
		virtual ~IDataConsumer() {}
		virtual void consume() = 0;
		void setData(const eeg::Data* data) { _data = data; }

	protected:
		const eeg::Data* _data{ nullptr };
	};

	class SimpleDataConsumer : public IDataConsumer
	{
	public:
		void consume() override;
	};
};
