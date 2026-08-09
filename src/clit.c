
// clit.c
// THIS CODE IS LICENSED UNDER THE MIT LICENSE
// SEE License IN ROOT DIRECTORY FOR MORE INFORMATION

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <stdlib.h>

#define CLIT_VERSION "Clit version 1.0.2\nFetch version 1.0.1\nmkcd version 1.0.1"

char *operatingsys = NULL;

void show_version() {
    printf("%s\n", CLIT_VERSION);
}

void show_help() {
    printf("usage:\n");
    printf("-h shows this help screen\n");
    printf("-v shows the current version\n");
    printf("fetch -u <url> -o <outfile>\n");
    printf("mkcd <directory> [directory...]\n");
}

void check_os() {
#if defined(_WIN32) || defined(_WIN64)
    operatingsys = "windows";
#elif defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
    operatingsys = "unix";
#else
    operatingsys = "unknown";
#endif
}

size_t fetch_write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        check_os();

        if (strcmp(argv[1], "-h") == 0) {
            show_help();
            return 0;

        } else if (strcmp(argv[1], "-v") == 0) {
            show_version();
            return 0;

        } else if (strcmp(argv[1], "fetch") == 0) {
            #if defined(_WIN32) || defined(_WIN64)

            #include <windows.h>
            #include <urlmon.h>

            #pragma comment(lib, "urlmon.lib")

            char *url = NULL;
            char *outfile_name = NULL;

            for (int argi = 2; argi < argc; argi++){
                if (strcmp(argv[argi], "-u") == 0 && argi + 1 < argc) {
                    url = argv[++argi];
                } else if (strcmp(argv[argi], "-o") == 0 && argi + 1 < argc) {
                    outfile_name = argv[++argi];
                }
            }

            HRESULT result = URLDownloadToFile(NULL, url, outfile_name, 0, NULL);
            if (result != S_OK) {
                printf("Download failed. Error code: 0x%08X\n", result);
                return 1;
            }

            return 0;
            #endif

            char *outfile_name = NULL;
            char *url = NULL;

            for (int argi = 2; argi < argc; argi++) {
                if (strcmp(argv[argi], "-u") == 0 && argi + 1 < argc) {
                    url = argv[++argi];
                } else if (strcmp(argv[argi], "-o") == 0 && argi + 1 < argc) {
                    outfile_name = argv[++argi];
                }
            }

            if (!url || !outfile_name) {
                printf("No url or outfile_name\n");
                return 1;
            }

            CURL *curl = curl_easy_init();

            if (curl) {
                FILE *fp = fopen(outfile_name, "wb");

                if (!fp) {
                    printf("Failed to open output file\n");
                    curl_easy_cleanup(curl);
                    return 1;
                }

                curl_easy_setopt(curl, CURLOPT_URL, url);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fetch_write_data);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

                CURLcode result = curl_easy_perform(curl);

                if (result != CURLE_OK) {
                    printf("curl error: %s\n", curl_easy_strerror(result));
                }

                fclose(fp);
                curl_easy_cleanup(curl);

                return result == CURLE_OK ? 0 : 1;

            } else {
                printf("Failed to initiate curl\n");
                return 1;
            }

        } else if (strcmp(argv[1], "mkcd") == 0) {
            int dirarrsz = 24;
            int dirsz = 51;

            char dirtargets[24][51];
            int dirsizes = 0;

            for (int argi = 2; argi < argc && dirsizes < dirarrsz; argi++) {
                strncpy(dirtargets[dirsizes], argv[argi], dirsz - 1);
                dirtargets[dirsizes][dirsz - 1] = '\0';
                dirsizes++;
            }

            for (int diri = 0; diri < dirsizes; diri++) {
                char command[124];

                snprintf(
                    command,
                    sizeof(command),
                    "mkdir \"%s\" && cd \"%s\"",
                    dirtargets[diri],
                    dirtargets[diri]
                );

                system(command);
            }

            return 0;

        } else if (strcmp(argv[1], "crun") == 0) {
            #if defined(_WIN32) || defined(_WIN64)
            
            char command[124];

            snprintf(
                command,
                sizeof(command),
                "gcc %s -o compiled.exe && compiled.exe && del compiled.exe",
                argv[2]
            );

            system(command);
            return 0;

            #endif

            char command[124];

            snprintf(
                command,
                sizeof(command),
                "gcc %s -o compiled && ./compiled && rm -f compiled",
                argv[2]
            );

            system(command);
            return 0;
        } else {
            printf("Invalid argument: %s\n", argv[1]);
            return 1;
        }

    } else {
        show_help();
        return 1;
    }
}
