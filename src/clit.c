// clit.c
// THIS CODE IS LICENSED UNDER THE MIT LICENSE
// SEE License IN ROOT DIRECTORY FOR MORE INFORMATION

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

#define CLIT_VERSION "Clit verison 1.0.0"

void show_version(){
    printf("%s\n", CLIT_VERSION);
}

void show_help(){
    printf("usage:\n");
    printf("-h shows this help screen\n");
    printf("-v shows the current version\n");
}

size_t fetch_write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}

int main(int argc, char *argv[]){
    if(argc >= 2){
        if(strcmp(argv[1], "-h") == 0){
            show_help();
            return 0;
        }else if(strcmp(argv[1], "-v") == 0){
            show_version();
            return 0;
        }else if (strcmp(argv[1], "fetch") == 0){
            char *outfile_name = NULL;
            char *url = NULL;

            for(int argi=2; argi<argc; argi++){
                if(strcmp(argv[argi], "-u") == 0){
                    url = argv[argi + 1];
                }else if (strcmp(argv[argi], "-o") == 0){
                    outfile_name = argv[argi + 1];
                }
            }

            if(!url || !outfile_name){
                printf("No url or outfile_name\n");
                return 1;
            }

            CURL *curl = curl_easy_init();
            if(curl){
                FILE *fp = fopen(outfile_name, "wb");
                curl_easy_setopt(curl, CURLOPT_URL, url);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fetch_write_data);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
                curl_easy_perform(curl);
                fclose(fp);
                curl_easy_cleanup(curl);
                return 0;
            }else{
                printf("Failed to initiate curl\n");
                return 1;
            }
        }else{
            printf("Invalid argument: %s\n", argv[1]);
            return 1;
        }
    } else {
        show_help();
        return 1;
    }
}
