#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h> // opendir(), readdir(), closedir()
#include <unistd.h> // getcwd()
#include <iostream> // cpp
#include <string>
#include <vector>
#include <algorithm> // sort
#include <utility> // pair
using namespace std;

vector<pair<int, string>> v;

int getsize(struct dirent *file)
{
	int size = 0;
	FILE *fp = fopen(file->d_name, "r");
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fclose(fp);

	return size;
}

int main(int argc, char **argv)
{
        DIR *dir_ptr = NULL; // 디렉토리 가르킬 포인터
        struct dirent *file = NULL;
        char env[1024];
        char buff[1024];
        //getcwd : 현재 작업 디렉토리 구함
        strncpy(env, getcwd(buff, 1024), sizeof(env));

        if((dir_ptr = opendir(env)) == NULL) // opendir함수로 dir_ptr에 디렉토리명 리턴받음
        {
                // 없으면
                printf("%s directory 에러.\n", env);
                return -1;
        }

       string arr = argv[0];
     
        
       if(arr  == "-S") // 크기순 정렬 option
       { cout << "command ls -S(print in size order): " << '\n';
                while((file = readdir(dir_ptr)) != NULL)
                {	
			int size = getsize(file);
			v.push_back(make_pair(size, file->d_name));
			
			
                }
		sort(v.begin(), v.end()); // 크기순 정렬
		for(auto x : v) cout << x.first << ' ' << x.second << endl;
       }

       else {
	      cout << "command ls: " << '\n';
	 while((file = readdir(dir_ptr)) != NULL)
        { //디렉토리내 파일명 출력

                printf("%s\n", file->d_name);

        }
	}

        closedir(dir_ptr);

        return 0;
}

