#include <stdlib.h>
#include <stdio.h>
#include <yajl_tree.h>
#include <string.h>

struct bases
{
    char *mass;
    char *distance;
    char *volume;
};

enum measurement_type
{
    mt_mass,
    mt_distance,
    mt_volume
};

struct ratio
{
    enum measurement_type type;
    double ratio;
    struct ratio *base;
    struct ratio *next;
};

struct all_data
{
    char *ratios_name;
    struct ratio ratio;
    struct bases bases;
};

int main(void)
{
    struct all_data mainDataBlock;
    static unsigned char fileData[65536];
    puts("welcome to the unit converter");
    puts("trying to access the ratios XML file...");
    size_t rd;
    yajl_val node;
    char errbuf[1024];
    fileData[0] = 0;
    errbuf[0] = 0;
    rd = fread((void *) fileData, 1, sizeof(fileData) - 1, stdin);
    if (rd == 0 && !feof(stdin))
    {
        fprintf(stderr, "an error happened trying to read the ratios XML file...\n");
        return EXIT_FAILURE;
    }
    else if (rd >= sizeof(fileData) - 1)
    {
        fprintf(stderr, "the ratios XML file is too big\n");
        return EXIT_FAILURE;
    }
    node = yajl_tree_parse((const char *) fileData, errbuf, sizeof(errbuf));
    if (node == NULL)
    {
        fprintf(stderr, "parse error: ");
        if (strlen(errbuf))
        {
            fprintf(stderr, " %s", errbuf);
        }
        else
        {
            fprintf(stderr, "unknown error");
        }
        fprintf(stderr, "\n");
        return EXIT_FAILURE;
    }
    char *base_volume;
    char *base_distance;
    char *base_mass;
    puts("parting the ratios XML file...");
    puts("looking for base->volume...");
    const char *path[] = { "base", "volume", (const char *) 0 };
    yajl_val v = yajl_tree_get(node, path, yajl_t_string);
    if (v)
    {
        puts("base->volume found.");
        base_volume = YAJL_GET_STRING(v);
        printf("base->volume == %s\n", base_volume);
    }
    else
    {
        fprintf(stderr, "error: base->volume not found\n");
        return EXIT_FAILURE;
    }
    puts("looking for base->distance...");
    const char *path2[] = { "base", "distance", (const char *) 0 };
    v = yajl_tree_get(node, path2, yajl_t_string);
    if (v)
    {
        puts("base->distance found.");
        base_distance = YAJL_GET_STRING(v);
        printf("base->distance == %s\n", base_distance);
    }
    else
    {
        fprintf(stderr, "error: base->distance not found\n");
        return EXIT_FAILURE;
    }
    puts("looking for base->mass...");
    const char *path3[] = { "base", "mass", (const char *) 0 };
    v = yajl_tree_get(node, path3, yajl_t_string);
    if (v)
    {
        puts("base->mass found.");
        base_mass = YAJL_GET_STRING(v);
        printf("base->mass == %s\n", base_mass);
    }
    else
    {
        fprintf(stderr, "error: base->mass not found\n");
        return EXIT_FAILURE;
    }
    puts("populating main data block with bases information...");
    mainDataBlock.bases.distance = base_distance;
    mainDataBlock.bases.volume = base_volume;
    mainDataBlock.bases.mass = base_mass;
    puts("getting the ratios name...");\
    char *ratios_file_name;
    const char *path4[] = {"name", (const char *)0, (const char *)0};
    v = yajl_tree_get(node, path4, yajl_t_string);
    if (v)
    {
        puts("name found.");
        ratios_file_name = YAJL_GET_STRING(v);
        printf("name == %s\n", ratios_file_name);
    }
    else
    {
        fprintf(stderr, "error: name not found\n");
        return EXIT_FAILURE;
    }
    puts("populating main data block with ratios name...");
    mainDataBlock.ratios_name = ratios_file_name;
    struct ratio *ll = malloc(sizeof(struct ratio));
    if (ll == NULL)
    {
        fprintf(stderr, "a malloc failed. you might be out of memory. quitting.\n");
        return EXIT_FAILURE;
    }
    puts("grabbing all of the actual ratios from the YAML ratios file...");
    puts("implementation is not complete yet. check back later...");
    return EXIT_SUCCESS;
}