#define MAX_FILES 16
#define MAX_FILENAME 32
#define MAX_FILESIZE 512

typedef struct {
    char name[MAX_FILENAME];
    char data[MAX_FILESIZE];
    int size;
    int used;
} File;

File filesystem[MAX_FILES];
int fs_initialized = 0;

void fs_init() {
    int i;
    for(i = 0; i < MAX_FILES; i++) {
        filesystem[i].used = 0;
        filesystem[i].size = 0;
    }
    fs_initialized = 1;
}

int fs_create(char* name) {
    int i;
    for(i = 0; i < MAX_FILES; i++) {
        if(!filesystem[i].used) {
            int j;
            for(j = 0; name[j] != 0 && j < MAX_FILENAME-1; j++)
                filesystem[i].name[j] = name[j];
            filesystem[i].name[j] = 0;
            filesystem[i].size = 0;
            filesystem[i].used = 1;
            return i;
        }
    }
    return -1;
}

int fs_find(char* name) {
    int i;
    for(i = 0; i < MAX_FILES; i++) {
        if(!filesystem[i].used) continue;
        int j = 0;
        while(filesystem[i].name[j] == name[j] && name[j] != 0) j++;
        if(filesystem[i].name[j] == name[j]) return i;
    }
    return -1;
}

int fs_write(char* name, char* data) {
    int idx = fs_find(name);
    if(idx == -1) idx = fs_create(name);
    if(idx == -1) return -1;
    int i;
    for(i = 0; data[i] != 0 && i < MAX_FILESIZE-1; i++)
        filesystem[idx].data[i] = data[i];
    filesystem[idx].data[i] = 0;
    filesystem[idx].size = i;
    return 0;
}

char* fs_read(char* name) {
    int idx = fs_find(name);
    if(idx == -1) return 0;
    return filesystem[idx].data;
}

int fs_delete(char* name) {
    int idx = fs_find(name);
    if(idx == -1) return -1;
    filesystem[idx].used = 0;
    filesystem[idx].size = 0;
    return 0;
}
