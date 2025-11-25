#include <stdint.h>

void SystemInit(void)
{
    /* Với QEMU MPS2-AN505, tạm thời không cần làm gì.
       Nếu sau này dùng clock phức tạp thì cấu hình ở đây. */
}

/* Chặn lỗi thiếu __aeabi_unwind_cpp_pr0 khi dùng -nostdlib */
void __aeabi_unwind_cpp_pr0(void)
{
    while (1) { }
}
