#include <jni.h>
#include <string>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/dvb/frontend.h>
#include <stdio.h>
#include <locale>
#include <fstream>
#include <android/log.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_ioctltest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++  Ravi";
    static struct dtv_property props[] = {
            { .cmd = DTV_DELIVERY_SYSTEM, .u.data = SYS_DVBC_ANNEX_A },
            { .cmd = DTV_FREQUENCY,       .u.data = 651000000 },
            { .cmd = DTV_MODULATION,      .u.data = QAM_256 },
            { .cmd = DTV_INVERSION,       .u.data = INVERSION_AUTO },
            { .cmd = DTV_SYMBOL_RATE,     .u.data = 5217000 },
            { .cmd = DTV_INNER_FEC,       .u.data = FEC_3_4 },
            { .cmd = DTV_TUNE }
    };

    static struct dtv_properties dtv_prop = {
            .num = 6, .props = props
    };

    __android_log_print(ANDROID_LOG_INFO, "Ravi", "trying open device file.");


    int fd = open("/dev/dvb/adapter0/frontend0", O_RDWR);

    if(fd < 0) {
        __android_log_print(ANDROID_LOG_INFO, "Ravi", "cannot open device file.");
        std::string fds = "cannot open device file";
        return env->NewStringUTF(fds.c_str());
        return 0;
    }

    if (ioctl(fd, FE_SET_PROPERTY, &dtv_prop) == -1) {
        __android_log_print(ANDROID_LOG_INFO, "Ravi", "Failed to set property via ioctl.");
        std::string fail = "Failed to set property";
        return env->NewStringUTF(fail.c_str());
    } else {
        __android_log_print(ANDROID_LOG_INFO, "Ravi", "Success to set property via ioctl.");
        std::string success = "ioctl Success ";
        return env->NewStringUTF(success.c_str());

    }
}
