#ifndef TYPES_H_
#define TYPES_H_

//#pragma pack(1) /*指定按2字节对齐*/
struct alignas(bool) Type_Cpp_t
{
    bool status;
    int number;
};
//#pragma pack()
extern "C"
{
    struct Type_C_t
    {
        bool status;
        int number;
    };
}
#endif