#include <rtdevice.h>
#include <rtthread.h>


#define LOG rt_kprintf

#define EXAMPLE_CAN_DEV_NAME "can0"

static rt_device_t example_can_dev = {0};
static struct rt_can_status status = {0};


int can_tx_example(int argc, char **argv)
{
    LOG("can tx example stated!\r\n");

    // 获取can设备句柄
    example_can_dev = rt_device_find(EXAMPLE_CAN_DEV_NAME);

    // 判断是否成功获取设备，如果不成功则直接返回
    if (example_can_dev == 0)
    {
        LOG("device %s not found\r\n", EXAMPLE_CAN_DEV_NAME);
        return 1;
    }
    else
    {
        LOG("device %s found\r\n", EXAMPLE_CAN_DEV_NAME);
    }

    // 中断发送+中断接收模式打开can设备
    {
        int ret = rt_device_open(example_can_dev, RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
        if (ret == RT_EOK)
        {
            LOG("success open device %s\r\n", EXAMPLE_CAN_DEV_NAME);
        }
        else
        {
            LOG("device %s open failed error code :%d", EXAMPLE_CAN_DEV_NAME, ret);
            return ret;
        }
    }

    //    // 配置波特率为1Mbps
    //    {
    //        int ret = rt_device_control(example_can_dev, RT_CAN_CMD_SET_BAUD, (void *)CAN500kBaud);
    //        if (ret == RT_EOK)
    //        {
    //            LOG("success set baud\r\n");
    //        }
    //        else
    //        {
    //            LOG("failed set baud error code :%d\r\n",ret);
    //            return;
    //        }
    //    }

    //    // 配置工作模式为正常模式
    //    {
    //        int ret = rt_device_control(example_can_dev, RT_CAN_CMD_SET_MODE, (void *)RT_CAN_MODE_NORMAL);
    //        if (ret == RT_EOK)
    //        {
    //            LOG("success set mode\r\n");
    //        }
    //        else
    //        {
    //            LOG("failed set mode error code :%d\r\n",ret);
    //            return;
    //        }
    //    }

    struct rt_can_msg msg = {0};
    int size = 0;
    msg.id = 0x205;         /* ID 为 0x78 */
    msg.ide = RT_CAN_STDID; /* 标准格式 */
    msg.rtr = RT_CAN_DTR;   /* 数据帧 */
    msg.len = 8;            /* 数据长度为 8 */
                            /* 待发送的 8 字节数据 */
    *(int16_t *)(msg.data + 0) = 2000;
    *(int16_t *)(msg.data + 2) = 2000;
    *(int16_t *)(msg.data + 4) = 2000;
    *(int16_t *)(msg.data + 6) = 2000;

//    can_send(example_can_dev, &msg, 0);
	rt_device_write(example_can_dev, 0, &msg, sizeof(msg));
    LOG("send\r\n");

    //     for (int i = 0; i < 100; i++)
    //     {
    //         if (0 == rt_device_write(example_can_dev, 0, &msg, sizeof(msg)))
    //         {
    //             LOG("%s write failed!\r\n", EXAMPLE_CAN_DEV_NAME);
    //             return;
    //         }
    //         rt_thread_delay(rt_tick_from_millisecond(10));
    //         LOG("send\r\n");
    //     }

    // msg.id = 0x78;          /* ID 为 0x78 */
    // msg.ide = RT_CAN_STDID; /* 标准格式 */
    // msg.rtr = RT_CAN_DTR;   /* 数据帧 */
    // msg.len = 8;            /* 数据长度为 8 */
    // /* 待发送的 8 字节数据 */
    // msg.data[0] = 0x00;
    // msg.data[1] = 0x11;
    // msg.data[2] = 0x22;
    // msg.data[3] = 0x33;
    // msg.data[4] = 0x44;
    // msg.data[5] = 0x55;
    // msg.data[6] = 0x66;
    // msg.data[7] = 0x77;
    /* 发送一帧 CAN 数据 */
    // size = rt_device_write(example_can_dev, 0, &msg, sizeof(msg));
    // if (size == 0)
    // {
    //     rt_kprintf("can dev write data failed!\n");
    // }

    return 0;
}

MSH_CMD_EXPORT(can_tx_example, can0tx);