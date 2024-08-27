/*
*
*	Author : amr
*                
*	OS : Debian 12 x86_64
*
*	Date : 23-Aug-2024
*
*   Project Name : ferr
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define CURRENT_LINE __LINE__
#define PREVIOUS_LINE __LINE__-1
#define LINE_OFFSET(offset) (__LINE__ - (offset))

#define NOTE_MESSAGE    1
#define WARNING_MESSAGE 2
#define ERROR_MESSAGE   3
#define EXIT            0
#define RETURN          1
#define NOTHING         2
#define NOLINE          0
#define SUCESS          0


int error_flag=0;
int ferr(int line, int type, int isexit, int exitcode,char* message, ...){
    // ferr is a function to manage error messages 
    // ferr(  int line, int type, int isexit, int exitcode, char* message, ...)
    //
    //   I- line: line number (use 0 if you do not want to display line number in the error message) 
    //
    //
    //  II- type ("default is (1/note)"): 
    //      1 : note (Default) (prints to stdout)
    //      2 : warning (prints to stdout)
    //      3 : error (prints to stdout)
    //
    //
    // III- isexit (optional "default is 1"):
    //      0 : exit after printing 
    //          (set exit code in the next
    //           arg, default error code
    //           is used if error code
    //           is not set).
    //      1 : return a status code after printing 
    //          (set return code in the next
    //           arg, default return code
    //           is used if return code
    //           is not set).
    //      2 : do not exit or return (exit code is useless)
    //
    //
    //  IV- error/return code (isexit should be set to 0 or 1 to be usefull): 
    //      to set error/return code, must be numeric, 
    //      if not numeric or not set, the default 
    //      value will be used. 
    //
    //
    //   V- message (format string): text to print (could be fomatted text i.e: 
    //      "your age is %d"), start passing format string arguments 
    //       after the exitcode argument
    //
    //  VI- formatted string argument (dynamic number of args using va_list)
    //
    //
    //
    //


    if (error_flag == 0 ){
        type = ( (type < 1) || (type > 3) ) ? 1 : type;
        isexit = ((isexit < 0) || (isexit > 2) ) ? 1 : isexit;
        char* typestr="";
        FILE *fd=stdout;
        va_list args;
        switch (type){  
        case 1:
            typestr="NOTE";
            break;   
        case 2:
            typestr="WARNING";
            break;
        case 3:
            typestr="ERROR";
            fd=stderr;
            break;
        default:
            type=1;
            typestr="NOTE";
        ;;
        }
        if(line >= 1){
            fprintf(fd,"[%s at line:%d]\n",typestr,line);
            va_start(args,message);
            vfprintf(fd,message,args);
            va_end(args);
            fprintf(fd,"\n[END %s]\n",typestr); 
        } else {
            fprintf(fd,"[%s]\n",typestr);
            va_start(args,message);
            vfprintf(fd,message,args);
            va_end(args);
            fprintf(fd,"\n[END %s]\n",typestr); 
        }
        if ( isexit ==  0 ){
            exit (exitcode);
        } else if ( isexit == 1 ){
            return exitcode;
        } else {
            return 0;
        } 
    } else {
        return 0;
    }
    
}

int main(int argc,char** argv){

    ferr(CURRENT_LINE,ERROR_MESSAGE,EXIT,9,"TEST in function %s, test id: %d",__FUNCTION__,99999);
    
}

    
