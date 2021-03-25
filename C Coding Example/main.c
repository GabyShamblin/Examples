#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "leak_detector_c.h"
#include "sp21_cop3502_as1.h"



        //--------File functions--------
// Removes carriage returns and line feeders (*From Dr. Gerber's lesson*)
void remove_crlf(char *s)
{
    char *t = s +strlen(s);

    t--;
    while((t >= s) && (*t == '\n' || *t == '\r'))
    {
        *t = '\0';
        t--;
    }
}

// Moves to the next non-blank line in the file (*From Dr. Gerber's lesson*)
int get_next_nonblank_line(FILE *in, char *buf, int max_length)
{
    buf[0] = '\0';

    while(!feof(in) && (buf[0] == '\0'))
    {
        fgets(buf, max_length, in);
        remove_crlf(buf);
    }

    if(buf[0] != '\0')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



        //--------Monster functions--------
//Print monsters to screen
void print_monster(monster *m)
{
    printf("Id: %d\n", m->id);
    printf("Name: %s\n", m->name);
    printf("Element: %s\n", m->element);
    printf("Population: %d\n\n", m->population);
}

// Reads monsters from input file
void read_monsters(FILE *in, monster *m)
{
    char buf[256], name[256], element[256];
    int population;

    // Read monster name, element, and population
    get_next_nonblank_line(in, buf, 255);
    sscanf(buf, "%s %s %d", name, element, &population);

    m->name = strdup(name);
    m->element = strdup(element);
    m->population = population;

    //print_monster(m);
}

// Creates monster index
monster *create_monster_index(FILE *in, monster *monsterIndex)
{
    char buf[256];

    // Find number of monsters
    get_next_nonblank_line(in, buf, 255);
    int numMonsters = atoi(buf);

    monsterIndex = calloc(sizeof(monster), numMonsters);

    // Read through all monsters
    for(int i = 0; i < numMonsters; i++)
    {
        monsterIndex[i].id = i;
        read_monsters(in, monsterIndex + i);
    }

    return monsterIndex;
}



        //--------Region functions--------
// Print regions to screen
void print_region(region *r)
{
    printf("\nName: %s\n", r->name);
    printf("nmonsters: %d\n", r->nmonsters);
    printf("Total Population: %d\n", r->total_population);

    for(int i = 0; i < r->nmonsters; i++)
    {
        print_monster(r->monsters[i]);
    }
}

// Reads regions and their monsters from input file
void read_regions(FILE *in, region *r, monster *m)
{
    char buf[256], name[256], monsterName[256];
    int numRegionMonsters, j = 0;

    // Read region name
    get_next_nonblank_line(in, buf, 255);
    sscanf(buf, "%s", name);
    r->name = strdup(name);

    // Read number of monsters in region
    get_next_nonblank_line(in, buf, 255);
    numRegionMonsters = atoi(buf);
    r->nmonsters = numRegionMonsters;

    r->monsters = calloc(sizeof(monster *), numRegionMonsters);

    // Read the monster names
    for(int i = 0; i < numRegionMonsters; i++)
    {
        get_next_nonblank_line(in, buf, 255);
        sscanf(buf, "%s", monsterName);

        r->monsters[i] = calloc(sizeof(monster), 1);
        while(strcmp(monsterName, m[j].name) != 0)
        {
            j++;
        }
        r->monsters[i]->id = m[j].id;
        r->monsters[i]->name = m[j].name;
        r->monsters[i]->element = m[j].element;
        r->monsters[i]->population = m[j].population;

        r->total_population += m[j].population;
    }
}

// Create region atlas
region *create_region_atlas(FILE *in, region *regionAtlas, monster *m)
{
    char buf[256];

    // Read number of regions
    get_next_nonblank_line(in, buf, 255);
    int numRegions = atoi(buf);

    regionAtlas = calloc(sizeof(region), numRegions);

    // Read through all regions
    for(int i = 0; i < numRegions; i++)
    {
        read_regions(in, regionAtlas + i, m);
    }

    return regionAtlas;
}



        //--------Trainer functions--------
// Print trainers to screen
void print_trainers(trainer *t)
{
    printf("\nName: %s\n", t->name);

    itinerary *it = t->visits;
    printf("Number of Regions Visited: %d\n", it->nregions);
    printf("Number of Monster Captures: %d\n", it->captures);

    for(int i = 0; i < it->nregions; i++)
    {
        print_region(it->regions[i]);
    }
}

// Reads trainer name and their itinerary
void read_trainers(FILE *in, trainer *t,  region *r)
{
    char buf[256], name[256], regionName[256];
    int numCaptures, numRegions, j = 0;

    t->visits = malloc(sizeof(itinerary));
    itinerary *it = t->visits;

    // Read trainer name
    get_next_nonblank_line(in, buf, 255);
    sscanf(buf, "%s", name);
    t->name = strdup(name);

    // Read number of captures
    get_next_nonblank_line(in, buf, 255);
    numCaptures = atoi(buf);
    it->captures = numCaptures;

    // Read number of regions
    get_next_nonblank_line(in, buf, 255);
    numRegions = atoi(buf);
    it->nregions = numRegions;

    it->regions = calloc(sizeof(region *), numRegions);

    // Read region names
    for(int i = 0; i < it->nregions; i++)
    {
        get_next_nonblank_line(in, buf, 255);
        sscanf(buf, "%s", regionName);

        it->regions[i] = calloc(sizeof(region), 1);
        while(strcmp(regionName, r[j].name) != 0)
        {
            j++;
        }
        it->regions[i]->name = r[j].name;
        it->regions[i]->nmonsters = r[j].nmonsters;
        it->regions[i]->total_population = r[j].total_population;
        it->regions[i]->monsters = r[j].monsters;
    }
}

// Creates trainer list
trainer *create_trainer_list(FILE *in, trainer *trainerList, region *regionAtlas, int numTrainers)
{
    trainerList = calloc(sizeof(trainer), numTrainers);

    // Read through all trainers
    for(int i = 0; i < numTrainers; i++)
    {
        read_trainers(in, trainerList + i, regionAtlas);
    }

    return trainerList;
}

// Reads the number of trainers
int num_trainers(FILE *in)
{
    char buf[256];

    get_next_nonblank_line(in, buf, 255);
    int numTrainers = atoi(buf);

    return numTrainers;
}



        //--------Calculations functions--------
// Calculates how much of each monster is captured
void calculations(FILE *out, region *r, int numCaptures)
{
    int monsterCom, totalCom = r->total_population;
    int numMonCaptures;

    // Go through monsters in the region
    for(int i = 0; i < r->nmonsters; i++)
    {
        monster *m = r->monsters[i];
        monsterCom = m->population;

        // Calculate how many monsters of each type will be captured
        numMonCaptures = round( ((float)monsterCom/(float)totalCom) * (float)numCaptures );

        if(numMonCaptures > 0)
        {
            // Print the monsters to file
            fprintf(out, "%d %s\n", numMonCaptures, m->name);
            printf("%d %s\n", numMonCaptures, m->name);
        }
    }
}

// Reads down to the regions
void read_numbers(FILE *out, trainer *t)
{
    itinerary *it = t->visits;

    fprintf(out, "%s\n", t->name);
    printf("%s\n", t->name);

    // Go through regions visited by trainer
    for(int j = 0; j < it->nregions; j++)
    {
        region *oneRegion = it->regions[j];

        fprintf(out, "%s\n", oneRegion->name);
        printf("%s\n", oneRegion->name);

        calculations(out, oneRegion, it->captures);
    }
    fprintf(out, "\n");
    printf("\n");
}



        //--------Free functions--------
//Partial destructor for trainerList
void clear_trainer(trainer *t)
{
    free(t->name);
    for(int i = 0; i < t->visits->nregions; i++)
    {
        free(t->visits->regions[i]);
    }
    free(t->visits->regions);
    free(t->visits);
}

//Partial destructor for regionAtlas
void clear_region(region *r)
{
    free(r->name);
    for(int i = 0; i < r->nmonsters; i++)
    {
        free(r->monsters[i]);
    }
    free(r->monsters);
}

//Partial destructor for monsterIndex
void clear_monster(monster *m)
{
    free(m->name);
    free(m->element);
}



int main()
{
    atexit(report_mem_leak);

    FILE *in;
    in = fopen("as1-sample-input.txt", "r");

    FILE *out;
    out = fopen("output.txt", "w");

    int i;

    // Create monster index
    monster *monsterIndex;
    monsterIndex = create_monster_index(in, monsterIndex);     // Pokedex works

    // Create region atlas
    region *regionAtlas;
    regionAtlas = create_region_atlas(in, regionAtlas, monsterIndex);       // Regions works

    // Create trainer list
    int numTrainers = num_trainers(in);
    trainer *trainerList;
    trainerList = create_trainer_list(in, trainerList, regionAtlas, numTrainers);       // Trainers works


    // Go through trainers
    for(i = 0; i < numTrainers; i++)
    {
        read_numbers(out, trainerList + i);
    }


    // Free all structures and close files
    fclose(in);
    fclose(out);

    for(i = 0; i < sizeof(trainerList); i++)
    {
        clear_trainer(trainerList + i);
    }
    for(i = 0; i < sizeof(regionAtlas); i++)
    {
        clear_region(regionAtlas + i);
    }
    for(i = 0; i < sizeof(monsterIndex); i++)
    {
        clear_monster(monsterIndex + i);
    }

    free(trainerList);
    free(regionAtlas);
    free(monsterIndex);

    return 0;
}
