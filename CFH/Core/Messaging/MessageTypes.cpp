#include "MessageTypes.h"

namespace CFH
{
	int Message::typeIdCounter_ = 0;

	int Message::GetNextTypeId()
	{
		return typeIdCounter_++;
	}
}