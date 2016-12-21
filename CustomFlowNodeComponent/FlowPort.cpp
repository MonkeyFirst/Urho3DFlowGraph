#include "FlowPort.h"

FlowOutputPort::FlowOutputPort(Context* context) :
    Object(context)
{

}

FlowInputPort::FlowInputPort(Context* context) :
    FlowOutputPort(context)
{
}

Variant FlowInputPort::ReadData()
{
    // Если нет соединения, то возвращаем пользовательскире данные.
    if (edge_.Expired())
        return data_;

    // Проверки на всякий случай. Вообще в лог добавить запись, чтобы отслеживать.
    if (edge_->fromPort_.Expired())
        return data_;

    return edge_->fromPort_->data_;
}
