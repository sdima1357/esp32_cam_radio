#include "storage.h"

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "esp_log.h"
#include "esp_spiffs.h"

static const char *TAG = "store";

esp_err_t storage_init(void)
{
    esp_vfs_spiffs_conf_t conf = {
        .base_path = STORAGE_BASE_PATH,
        .partition_label = "storage",
        .max_files = 4,
        .format_if_mount_failed = true,
    };

    esp_err_t err = esp_vfs_spiffs_register(&conf);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "mount failed: %s", esp_err_to_name(err));
        return err;
    }

    size_t total = 0, used = 0;
    esp_spiffs_info(conf.partition_label, &total, &used);
    ESP_LOGI(TAG, "spiffs mounted: %u/%u bytes used", (unsigned)used, (unsigned)total);
    return ESP_OK;
}

bool storage_exists(const char *path)
{
    struct stat st;
    return stat(path, &st) == 0;
}

int storage_read(const char *path, char *buf, size_t size)
{
    if (size == 0) {
        return -1;
    }
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        return -1;
    }
    size_t n = fread(buf, 1, size - 1, f);
    fclose(f);
    buf[n] = '\0';
    return (int)n;
}

esp_err_t storage_write(const char *path, const char *data, size_t len)
{
    FILE *f = fopen(path, "w");
    if (f == NULL) {
        ESP_LOGE(TAG, "cannot open %s for writing", path);
        return ESP_FAIL;
    }
    size_t n = fwrite(data, 1, len, f);
    fclose(f);
    if (n != len) {
        ESP_LOGE(TAG, "short write on %s", path);
        return ESP_FAIL;
    }
    return ESP_OK;
}

esp_err_t storage_write_default(const char *path, const char *data)
{
    if (storage_exists(path)) {
        return ESP_OK;
    }
    ESP_LOGI(TAG, "creating %s", path);
    return storage_write(path, data, strlen(data));
}
