#include <QCoreApplication>
#include <hidapi.h>
#include <QDebug>

void checkusbhid()
{
    struct hid_device_info *devs, *cur_dev;

    if (hid_init())
        return ;

    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs;
    while (cur_dev) {
        printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
        printf("\n");
        printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
        printf("  Product:      %ls\n", cur_dev->product_string);
        printf("  Release:      %hx\n", cur_dev->release_number);
        printf("  Interface:    %d\n",  cur_dev->interface_number);
        printf("\n");
        cur_dev = cur_dev->next;
    }
    hid_free_enumeration(devs);
}

void getusbhid()
{
    hid_device *devs;
    devs = hid_open(0x0738, 0x2221, NULL);
    QByteArray buf;
    buf.resize(11);
    int len = 0;
    while (len = hid_read(devs, (uchar*)(buf.data()), buf.size())) {
        qDebug() << buf.toHex();
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    checkusbhid();
    getusbhid();

    return a.exec();
}
