#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define size_of_url 100
#define http_port 80
#define endOfHostName 3



bool findPort(char* url,int *port,int* sizePort);
char** divideURL(char * url,int size,int* port,int* size_divide);
int creatFile(char** path,int size,bool findFile);
char* getPathRequset(char** path,int size,bool findFile);
char* hGetPath(char** path,int size,bool findFile);

bool findPort(char* url,int *port,int* sizePort)
{
    char*found=strstr(url,":");
    char* checkPort=strtok(url,":");
    checkPort=strtok(NULL,":");
    checkPort=strtok(NULL,":");
    if(found !=NULL)
    {
        int i=0;
        if(checkPort == NULL)
            return false;
        while (checkPort[i]!= '/' )
        {
            if(checkPort[i] == '\0')
                break;
            i++;
        }
        char chPort[i];

        int j;
        for(j=0;j<i;j++)
        {
            chPort[j]=checkPort[j];
        }
        *sizePort=i;
        chPort[i]='\0';
        *port=atoi(chPort);
        return true;
    }
    else
    {
        *port=http_port;
        return false;
    }
}

char** divideURL(char * url,int size,int* port,int* size_divide)
{
    int sizePort=0;
    char url1[size+1];
    char url2[size+1];
    strcpy(url1,url);
    strcpy(url2,url);
    
    char* foundOK =strstr(url,"http://");
    char* path=strtok(url,"/");
    if (foundOK != NULL)
    {
        path=strtok(NULL,"/");
    }
    int sizep=strlen(path)+1;
    char path1[sizep];
    strcpy(path1,path);
    int sizeDibide=0;
    while(path != NULL)
    {
        path=strtok(NULL,"/");
        sizeDibide++;
    }  

    char* hostName;
    int sizeHostName;
    if(findPort(url1,port,&sizePort))
    {
        sizeHostName=strlen(path1)-sizePort;
        hostName=malloc(sizeof(char)*sizeHostName);
        for(int i=0;i<sizeHostName;i++)
        {
            // if(i <sizePath1)
            //     hostName[i]=path1[i];
            if(path1[i] == ':')
                break;
            // else
            // {
                hostName[i]=path1[i];//i-sizePath1
            // }
        }
        hostName[sizeHostName-1]='\0';
    }
    else
    {
        sizeHostName=strlen(path1);
        hostName=malloc(sizeof(char)*(sizeHostName+1));
        for(int i=0;i<sizeHostName ;i++)
            hostName[i]=path1[i];
        if(hostName[sizeHostName-1] == ':')
            hostName[sizeHostName-1]='\0';
        hostName[sizeHostName]='\0';
    }
    
    
    *size_divide=sizeDibide;
    char** divide=(char**)malloc(sizeof(char*)*(sizeDibide));
    divide[0]=hostName;
    char* token=strtok(url2,"/");
    token=strtok(NULL,"/");
    int index=1;
    token=strtok(NULL,"/");
    while(token != NULL)
    {
        int sizet=strlen(token)+1;
        divide[index]=malloc(sizeof(char)*sizet);
        strcpy(divide[index],token);
        divide[index][sizet-1]='\0';
        token=strtok(NULL,"/");
        index++;
    }
    return divide;

}

int creatFile(char** path,int size,bool findFile)
{
    int sizeh=strlen(path[0])+size;
       
    if(size == 1)
    {
        char* str="index.html";
        sizeh+=strlen(str)+2;
        char hostName[sizeh];
        strcpy(hostName,path[0]);
        mkdir(hostName,0777);
        // if(!findFile)
        //     strcat(hostName,"index.html"); 
        // else   
            strcat(hostName,"/index.html");

        int fileDescriptor=open(hostName,O_WRONLY | O_CREAT,0644);
        if (fileDescriptor == -1) 
        {
            perror("open file");
            exit(1);
        }
        return fileDescriptor;  
    }
    for(int i=1;i<size;i++)
    {
        sizeh+=strlen(path[i]);
    }
    char hostName[sizeh];
    strcpy(hostName,path[0]);
    mkdir(hostName,0777);
    for(int i=1;i < size;i++)
    {
        strcat(hostName,"/");
        strcat(hostName,path[i]);
        if(i == size-1 )
        {
            if(!findFile)
            {
                mkdir(hostName,0777);
                strcat(hostName,"/index.html");
            }
            int fileDescriptor=open(hostName,O_WRONLY | O_CREAT,0644);
            if (fileDescriptor == -1) 
            {
                perror("open file");
                exit(1);
            }

            return fileDescriptor;
        }
        mkdir(hostName,0777);

    }
    return -1;
}

char* hGetPath(char** path,int size,bool findFile)
{
    char* index="/index.html";
    if(size == 1)
    {
        char *allPath;  
        int sizep=strlen(path[0])+1+strlen(index);
        allPath=malloc(sizeof(char)*sizep);
        strcpy(allPath,path[0]);
        strcat(allPath,index);
        return allPath;
    }
    int sizep=strlen(path[0])+size+1;
    if(!findFile)
        sizep+=strlen(index);
    for(int i=1;i<size;i++)
    {
        sizep+=strlen(path[i]);
    }
    char *allPath=malloc(sizeof(char)*sizep);
    strcpy(allPath,path[0]);
    for(int i=1;i < size;i++)
    {
        strcat(allPath,"/");
        strcat(allPath,path[i]);
    }
    if(!findFile)
        strcat(allPath,index);
    return allPath;
}

char* getPathRequset(char** path,int size,bool findFile)
{
    int sizep=0;
    for(int i=1;i<size;i++)
    {
        sizep+=strlen(path[i]);
    }
    sizep+=size;
    if(size == 1)
    {
        return NULL;
    }
    else
    {
        char* path2=malloc(sizeof(char)*sizep);
        strcpy(path2,path[1]);
        for(int i=2;i<size;i++)
        {
            strcat(path2,"/");
            strcat(path2,path[i]);
        }
        if(!findFile)
            strcat(path2,"/");
        return path2;
    }
}

int main(int argc,char * argv[])
{
   
    if(argc >3 || argc<2)
    {
        printf("Usage: cproxy <URL> [-s]");
        exit(1);
    }
    if((argc == 3 && strcmp(argv[2],"-s")) || strstr(argv[1],"https://") != NULL)
    {
        printf("Usage: cproxy <URL> [-s]");
        exit(1);
    }

    char* url=argv[1];
    int sizeURL=strlen(url);
    int port =http_port;
    // printf("./cproxy ");
    
    int sizePath=0;
    bool findFile=true;
    if(url[sizeURL-1] == '/')
        findFile=false;
    char** path=divideURL(url,sizeURL,&port,&sizePath);
    
    char* allPath=hGetPath(path,sizePath,findFile);
    int fd=open(allPath,O_RDWR,0644);
    free(allPath);
    int sizeReadFile=1000;
    if(fd == -1)
    {
        // printf("%s\n",path[0]);
        struct  hostent* host_info=gethostbyname(path[0]);  
        if(host_info == NULL)
        {
            herror("gethostbyname") ;// check if is exit()
            exit(1);
        }
        int sockfd =-1;
        if((sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == -1)
        {
            perror("socket failed");
            exit(1); 
        }
   
        struct sockaddr_in mysocket;
        memset(&mysocket,0,sizeof(struct sockaddr_in));
        mysocket.sin_family=AF_INET;
        mysocket.sin_port=htons(port);
        // mysocket.sin_addr.s_addr=host_address->s_addr;
        mysocket.sin_addr.s_addr=((struct in_addr*)host_info->h_addr)->s_addr;
        // memcpy(&mysocket.sin_addr.s_addr,host_info->h_addr_list,4);
        char* str1="GET /";
        char* str2=" HTTP/1.0\r\nHost: ";
        char* str3="\r\n\r\n";
        char* requestPath=getPathRequset(path,sizePath,findFile);
        int sizeRequest;
        if(requestPath != NULL)
        {
            sizeRequest=strlen(str1)+strlen(str2)+strlen(str3)+strlen(requestPath)+strlen(path[0])+1;
        }
        else
        {
            sizeRequest=strlen(str1)+strlen(str2)+strlen(str3)+strlen(path[0])+1;
        }
        char request[sizeRequest];
        strcpy(request,str1);
        if(requestPath != NULL)
        {
            strcat(request,requestPath);
            free(requestPath);
        }
        strcat(request,str2);
        strcat(request,path[0]);
        strcat(request,str3);
        request[sizeRequest-1]='\0';
        printf("HTTP request =\n%s\nLEN = %d\n",request,sizeRequest-1);
        
        if(connect(sockfd,(struct sockaddr*)&mysocket,sizeof(struct sockaddr_in)) == -1)
        {
            perror("Connection refused");
            for(int i=0;i<sizePath;i++)
            {
                free(path[i]);
            }
            free(path);
            close(sockfd);
            exit(0);
        }
        ssize_t bytesWritten= write(sockfd,request,strlen(request));
        if( bytesWritten == -1)
        {
            perror("faild wirte sockfd");
            exit(1);
        }

        bool check=false;
        bool findBody=false;
        
        unsigned char readFile[sizeReadFile];
        int content_length=0;
        ssize_t bytesRead= read(sockfd,readFile,sizeReadFile-1);
        if(bytesRead == -1)
        {
            perror("read");
            exit(1);
        }
        readFile[bytesRead]='\0';
        int fileDescriptor=-1;
        int sizeBody=0;
        int once=0;
        while(bytesRead > 0)
        {
            content_length+=bytesRead;
            readFile[bytesRead]='\0';
            if(bytesRead == -1)
            {
                perror("read");
                exit(1);
            }
            if(!check)
            {
                char* foundOK =strstr((char*)readFile,"200 OK");
                if (foundOK != NULL)
                {
                    check=true;
                    fileDescriptor= creatFile(path,sizePath,findFile);
                }
            }
            if(!findBody)
            {
                char* found1 =strstr((char*)readFile,"\r\n\r\n");
                if (found1 != NULL)
                {
                    findBody=true;
                }
            }
            if(findBody && check)
            {
                if(once == 0)
                {
                    char* found1 =strstr((char*)readFile,"\r\n\r\n");
                    once++;
                    int sizefound1=strlen(found1)-4;
                    
                    ssize_t bytesWritten1= write(fileDescriptor,found1+4,sizefound1);
                    if(bytesWritten1 == -1)
                    {
                        perror("read");
                        exit(1);
                    }
                    sizeBody+=bytesWritten1;
                    once++;
                    printf("%s",readFile);
                }
                else
                {
                    printf("%s",readFile);
                    ssize_t bytesWritten1= write(fileDescriptor,readFile,bytesRead);
                    if(bytesWritten1 == -1)
                    {
                        perror("read");
                        exit(1);
                    }
                    sizeBody+=bytesWritten1;
                }
            }
            else
            {
                printf("%s",readFile);
            }
            // printf("%s",readFile);
            bytesRead= read(sockfd,readFile,sizeReadFile-1);
        }
        close(fileDescriptor);
        close(sockfd);
        if(check)
        {
            printf("\n Total response bytes: %d\n",content_length);
        }
        
    }
    else
    {
        struct stat fileInto;
        if(fstat(fd,&fileInto) != 0)
        {
            perror("file size");
            exit(1);
        }
        int sizeBody=fileInto.st_size;
        int content_length=sizeBody;
        printf("File is given from local filesystem\n");
        content_length+= printf("HTTP/1.0 200 OK\r\nContent-Length: %d\r\n\r\n",sizeBody);
        unsigned char reader[1000]="";
        ssize_t bytes= read(fd,reader,sizeReadFile-1);
        reader[bytes]='\0';
        int i=bytes;
        while(bytes > 0)
        { 
            if(bytes == -1)
            {
                perror("read");
                exit(1);
            }
            printf("%s",reader);
            bytes= read(fd,reader,sizeReadFile-1);
            reader[bytes]='\0';
            i+=bytes;
        }
        printf("\n Total response bytes: %d\n",content_length);
    }
    
    for(int i=0;i<sizePath;i++)
    {
        free(path[i]);
    }
    free(path);
    if(argc == 3 && strcmp(argv[2],"-s") == 0)
        system(argv[3]);
    
}










