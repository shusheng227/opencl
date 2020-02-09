#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cassert>

#ifdef APPLE
#include <opencl/cl.h>
#else
#include <CL/cl.h>
#endif

/*
 * 修改自官方示例intel_ocl_caps_basic_win，用于测试手工配置项目
*/
int main()
{
    using namespace std;

    const char* required_platform_subname = "Intel";
    
    //函数返回值，CL_SUCCESS表示成功
    cl_int err = CL_SUCCESS;

    // 判断返回值是否正确的宏
#define CAPSBASIC_CHECK_ERRORS(ERR)        \
    if(ERR != CL_SUCCESS)                  \
    {                                      \
    cerr                                   \
    << "OpenCL error with code " << ERR    \
    << " happened in file " << __FILE__    \
    << " at line " << __LINE__             \
    << ". Exiting...\n";                   \
    exit(1);                               \
    }


    // 遍历系统中所有OpenCL平台
    cl_uint num_of_platforms = 0;
    // 得到平台数目
    err = clGetPlatformIDs(0, 0, &num_of_platforms);
    CAPSBASIC_CHECK_ERRORS(err);
    cout << "Number of available platforms: " << num_of_platforms << endl;

    cl_platform_id* platforms = new cl_platform_id[num_of_platforms];
    // 得到所有平台的ID
    err = clGetPlatformIDs(num_of_platforms, platforms, 0);
    CAPSBASIC_CHECK_ERRORS(err);


    //列出所有平台
    cl_uint selected_platform_index = num_of_platforms;

    cout << "Platform names:\n";

    for (cl_uint i = 0; i < num_of_platforms; ++i)
    {
        size_t platform_name_length = 0;
        err = clGetPlatformInfo(
            platforms[i],
            CL_PLATFORM_NAME,
            0,
            0,
            &platform_name_length
        );
        CAPSBASIC_CHECK_ERRORS(err);

        // 调用两次，第一次是得到名称的长度
        char* platform_name = new char[platform_name_length];
        err = clGetPlatformInfo(
            platforms[i],
            CL_PLATFORM_NAME,
            platform_name_length,
            platform_name, NULL
        );
        CAPSBASIC_CHECK_ERRORS(err);

        cout << "    [" << i << "] " << platform_name;

        if (
            strstr(platform_name, required_platform_subname) &&
            selected_platform_index == num_of_platforms // have not selected yet
            )
        {
            cout << " [Selected]";
            selected_platform_index = i;
        }

        cout << endl;
        delete[] platform_name;
    }
    delete[] platforms;
    return 0;
}