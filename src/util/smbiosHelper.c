#include "smbiosHelper.h"
#include "common/io/io.h"

bool ffIsSmbiosValueSet(FFstrbuf* value)
{
    return
        value->length > 0 &&
        !ffStrbufStartsWithIgnCaseS(value, "To be filled") &&
        !ffStrbufStartsWithIgnCaseS(value, "To be set") &&
        !ffStrbufStartsWithIgnCaseS(value, "OEM") &&
        !ffStrbufStartsWithIgnCaseS(value, "O.E.M.") &&
        !ffStrbufIgnCaseEqualS(value, "None") &&
        !ffStrbufIgnCaseEqualS(value, "System Product") &&
        !ffStrbufIgnCaseEqualS(value, "System Product Name") &&
        !ffStrbufIgnCaseEqualS(value, "System Product Version") &&
        !ffStrbufIgnCaseEqualS(value, "System Name") &&
        !ffStrbufIgnCaseEqualS(value, "System Version") &&
        !ffStrbufIgnCaseEqualS(value, "Default string") &&
        !ffStrbufIgnCaseEqualS(value, "Undefined") &&
        !ffStrbufIgnCaseEqualS(value, "Not Specified") &&
        !ffStrbufIgnCaseEqualS(value, "Not Applicable") &&
        !ffStrbufIgnCaseEqualS(value, "Not Defined") &&
        !ffStrbufIgnCaseEqualS(value, "Not Available") &&
        !ffStrbufIgnCaseEqualS(value, "INVALID") &&
        !ffStrbufIgnCaseEqualS(value, "Type1ProductConfigId") &&
        !ffStrbufIgnCaseEqualS(value, "All Series") &&
        !ffStrbufIgnCaseEqualS(value, "N/A")
    ;
}

#ifdef __linux__
void ffGetSmbiosValue(const char* devicesPath, const char* classPath, FFstrbuf* buffer)
{
    if (ffReadFileBuffer(devicesPath, buffer))
    {
        ffStrbufTrimRightSpace(buffer);
        if(ffIsSmbiosValueSet(buffer))
            return;
    }

    if (ffReadFileBuffer(classPath, buffer))
    {
        ffStrbufTrimRightSpace(buffer);
        if(ffIsSmbiosValueSet(buffer))
            return;
    }

    ffStrbufClear(buffer);
}
#endif
