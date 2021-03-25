typedef struct monster {
	int id;
	char *name;
	char *element;
	int population;     // Commonality
} monster;

typedef struct region {
	char *name;
	int nmonsters;
	int total_population;   // Commonality added up
	monster **monsters;
} region;

typedef struct itinerary {
	int nregions;
	region **regions;
	int captures;
} itinerary;

typedef struct trainer {
	char *name;
	itinerary *visits;
} trainer;
