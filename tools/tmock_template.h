#ifndef __${FILENAME_H}_
#define __${FILENAME_H}_

#include "tmock.h"
#include "${headerFilePath}"

<%
filename = headerFileName.split('.')[0].title()
%>
% if len(functions) > 0:
class MockGlobal${filename}
{
    public:
        TMOCK_CLASS(MockGlobal${filename});
        % for method in functions:
        <%
        parameters_define_list = [m["type"] + ' ' + m["name"] for m in method["parameters"]]
        parameters_define_count = len(parameters_define_list)
        parameters_define = ', '.join(parameters_define_list)
        full_functionname = '::'.join([ n.strip('::') for n in [method["namespace"], method["name"]] if n != ''])
        return_type = method["rtnType"][7:] if method["rtnType"].startswith('static ') else method["rtnType"]
        %>
        TMOCK_METHOD${parameters_define_count}("${full_functionname}", ${method["name"]}, ${return_type}(${parameters_define}));
        % endfor
};
% endif

% for classname in classList:
<%
full_classname = '::'.join([ n.strip('::') for n in [classList[classname]["namespace"], classname] if n != ''])
method_list = classList[classname]["methods"]["public"] + classList[classname]["methods"]["private"] + classList[classname]["methods"]["protected"]
%>
class Mock${classname}
{
    public:
        TMOCK_CLASS(Mock${classname});
        % for method in method_list: 
            % if not method["constructor"] and not method["destructor"]:
            <%
            parameters_define_list = [m["type"] + ' ' + m["name"] for m in method["parameters"]]
            if not method["static"]: parameters_define_list = [full_classname + '* thisValue'] + parameters_define_list
            parameters_define_count = len(parameters_define_list)
            parameters_define = ', '.join(parameters_define_list)
            full_functionname = '::'.join([ n.strip('::') for n in [method["namespace"], classname, method["name"]] if n != ''])
            return_type = method["rtnType"][7:] if method["rtnType"].startswith('static ') else method["rtnType"]
            %>
        TMOCK_METHOD${parameters_define_count}("${full_functionname}", ${method["name"]}, ${return_type}(${parameters_define}));
            % endif
        % endfor
};
% endfor

#endif
