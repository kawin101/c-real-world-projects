#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void organize_files(const char *directory)
{
  struct dirent *entry;
  DIR *dp = opendir(directory);

  if (dp == NULL)
  {
    perror("opendir failed");
    return;
  }

  while ((entry = readdir(dp)) != NULL)
  {
    if (entry->d_type == DT_REG)
    {
      char *ext = strrchr(entry->d_name, '.');
      if (ext)
      {
        char target_folder[256];
        snprintf(target_folder, sizeof(target_folder), "%s/%s", directory, ext + 1);
        mkdir(target_folder, 0777);

        char src[256], dest[256];
        snprintf(src, sizeof(src), "%s/%s", directory, entry->d_name);
        snprintf(dest, sizeof(dest), "%s/%s/%s", directory, ext + 1, entry->d_name);

        rename(src, dest);
        printf("Moved %s -> %s\n", src, dest);
      }
    }
  }
  closedir(dp);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <directory>\n", argv[0]);
    return 1;
  }
  organize_files(argv[1]);
  return 0;
}
