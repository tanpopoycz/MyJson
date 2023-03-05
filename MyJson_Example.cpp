#include <iostream>
#include "cJSON.h"
#include <typeinfo>
//#include <exception>
#include "cJSON_class_def.h"

//NOTE: Returns a heap allocated string, you are required to free it after use.
char* create_monitor_with_helpers(void)
{
    const unsigned int resolution_numbers[3][2] = {
        {1280, 720},
        {1920, 1080},
        {3840, 2160}
    };
    char* string = NULL;
    cJSON* resolutions = NULL;
    size_t index = 0;

    cJSON* monitor = cJSON_CreateObject();
    cJSON* monitor_copy = NULL;
    
    cJSON* str = NULL;
    str = cJSON_AddStringToObject(monitor, "name", "Awesome 4K");
    if (str == NULL)
    {
        goto end;
    }
    str = cJSON_AddStringToObject(monitor, "sex", "man");
    if (str == NULL)
    {
        goto end;
    }
    std::cout << "=========================" << "\n";
    std::cout << str->string << "\n";
    std::cout << str->valuedouble << "\n";
    std::cout << str->valueint << "\n";
    std::cout << str->valuestring << "\n";
    std::cout << "=========================" << "\n";


    resolutions = cJSON_AddArrayToObject(monitor, "resolutions");
    if (resolutions == NULL)
    {
        goto end;
    }

    for (index = 0; index < (sizeof(resolution_numbers) / (2 * sizeof(int))); ++index)
    {
        cJSON* resolution = cJSON_CreateObject();

        if (cJSON_AddNumberToObject(resolution, "width", resolution_numbers[index][0]) == NULL)
        {
            goto end;
        }

        if (cJSON_AddNumberToObject(resolution, "height", resolution_numbers[index][1]) == NULL)
        {
            goto end;
        }

        cJSON_AddItemToArray(resolutions, resolution);
    }

    string = cJSON_Print(monitor);
    if (string == NULL)
    {
        fprintf(stderr, "Failed to print monitor.\n");
        goto end;
    }
    std::cout << "============monitor=============" << "\n";
    std::cout << string << "\n";
    std::cout << "monitor" << monitor << "\n";
    std::cout << "monitor->next" << monitor->next << "\n";
    std::cout << "monitor->prev" << monitor->prev << "\n";
    std::cout << "monitor->child" << monitor->child << "\n";

    std::cout << "monitor->child->next--->" << monitor->child->next << "\n";
    std::cout << "monitor->child->prev--->" << monitor->child->prev << "\n";
    std::cout << "monitor->child->child--->" << monitor->child->child << "\n";
    std::cout << "monitor->child->type--->" << monitor->child->type << "\n";
    std::cout << "monitor->child->string--->" << monitor->child->string << "\n";
    std::cout << "monitor->child->valuestring--->" << monitor->child->valuestring << "\n";
    std::cout << "============================================" <<  "\n";

    std::cout << "monitor->child->next->next --->" << monitor->child->next->next << "\n";
    std::cout << "monitor->child->next->prev --->" << monitor->child->next->prev << "\n";
    std::cout << "monitor->child->next->child --->" << monitor->child->next->child << "\n";
    std::cout << "monitor->child->next->type --->" << monitor->child->next->type << "\n";
    std::cout << "monitor->child->next->string --->" << monitor->child->next->string << "\n";
    std::cout << "monitor->child->next->valuestring --->" << monitor->child->next->valuestring << "\n\n";


    std::cout << "monitor->child->next->next->next ===\t" << monitor->child->next->next->next << "\n";
    std::cout << "monitor->child->next->next->prev ===\t" << monitor->child->next->next->prev << "\n";
    std::cout << "monitor->child->next->next->child ===\t" << monitor->child->next->next->child << "\n";
    std::cout << "monitor->child->next->next->child ===\t" << monitor->child->next->next->type << "\n";
    std::cout << "monitor->child->next->next->string ===\t" << monitor->child->next->next->string << "\n";
    //std::cout << "monitor->child->next->next->valuestring ===\t" << monitor->child->next->next->valuestring << "\n";

    std::cout << "=========================" << "\n";

    try
    { 
        monitor_copy = cJSON_DeepCopyFromObject(monitor);
    }
    catch(std::exception &e)
    {
        std::cout << "cJSON_DeepCopyFromObject:======> " << e.what() << "\n";
    }
    
    if (!monitor_copy)
    {
        fprintf(stderr, "Failed to cJSON_CreateObjectReference from monitor.\n");
        goto end;
    }
    cJSON_Delete(monitor);
    fprintf(stderr, "==============copy==================>");
    string = cJSON_Print(monitor_copy);

    std::cout << string << "\n";
    

end:
    cJSON_Delete(monitor);
    cJSON_Delete(monitor_copy);

    return string;
}


/* ½âÎö */
/* return 1 if the monitor supports full hd, 0 otherwise */
int supports_full_hd(const char* const monitor)
{
    const cJSON* resolution = NULL;
    const cJSON* resolutions = NULL;
    const cJSON* name = NULL;
    int status = 0;
    cJSON* monitor_json = cJSON_Parse(monitor);
    if (monitor_json == NULL)
    {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        status = 0;
        goto end;
    }

    name = cJSON_GetObjectItemCaseSensitive(monitor_json, "name");
    if (cJSON_IsString(name) && (name->valuestring != NULL))
    {
        printf("Checking monitor \"%s\"\n", name->valuestring);
    }

    resolutions = cJSON_GetObjectItemCaseSensitive(monitor_json, "resolutions");
    cJSON_ArrayForEach(resolution, resolutions)
    {
        cJSON* width = cJSON_GetObjectItemCaseSensitive(resolution, "width");
        cJSON* height = cJSON_GetObjectItemCaseSensitive(resolution, "height");

        if (!cJSON_IsNumber(width) || !cJSON_IsNumber(height))
        {
            status = 0;
            goto end;
        }

        if ((width->valuedouble == 1920) && (height->valuedouble == 1080))
        {
            status = 1;
            goto end;
        }
    }

end:
    cJSON_Delete(monitor_json);
    return status;
}




void p_strlen(char* str)
{
    std::cout << strlen(str) << "\n";
}


int main()
{
    using namespace std;

    //cout << create_monitor_with_helpers() << "\n";

    MAIL m;
    m.status.err_code = 200;
    m.status.err_msg = "OK";
    m.mail = "jerry@qwe.com";
    m.status1.err_code = 400;
    m.status1.err_msg = "NOT OK";

    STATUS s;
    s.err_code = 0;
    s.err_msg = "Success";

    try {
        MyCJson::MyCJson j = m;
        cout << j.dump() << "\n";

        //j = s;
        //cout << j.dump() << "\n\n";

        try
        {
            MAIL z;
            j.get_to(z);
            cout << z.status.err_code << endl;
            cout << z.status.err_msg << endl;
            cout << z.mail << endl;
            cout << z.status1.err_code << endl;
            cout << z.status1.err_msg << endl;
        }
        catch(exception& e)
        {
            cout << e.what() << "\n";
        }
       


    }
    catch(exception &e)
    {
        cout << e.what() << "\n";
    }

 
}