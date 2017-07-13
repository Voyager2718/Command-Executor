#include"yrandom.h"

namespace yrandom{
    unsigned int Random(unsigned int min, unsigned int max) {
        assert(min < max);
        assert(min >= 0);
        unsigned int rnum = 0;
    #if defined _MSC_VER
        HCRYPTPROV hProvider = 0;
        const DWORD dwLength = sizeof(int);
        BYTE pbBuffer[dwLength] = {};
        DWORD result =::CryptAcquireContext(&hProvider, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
        assert(result);
        result = ::CryptGenRandom(hProvider, dwLength, pbBuffer);
        rnum = *(unsigned int*)pbBuffer;
        assert(result);
        ::CryptReleaseContext(hProvider, 0);
    #elif defined __GNUC__
        int fd = open("/dev/urandom", O_RDONLY);
        if (fd != -1) {
            (void) read(fd, (void *) &rnum, sizeof(int));
            (void) close(fd);
        }
    #endif
        return static_cast<unsigned int>(rnum%(max) + min + 1);
    }
}