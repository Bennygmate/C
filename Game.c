Game.h (Just the struct part)

// Needed for the Game struct
typedef struct _ARCGrant {
     int startVertexID;
     int endVertexID;
     bits8 owner; // Stores the player who owns this grant
 } ARCGrant;


typedef struct _game {
     // Store the current turn number (obvious)
     int currentTurn;
     // Store each tiles discipline going from 0 to 18 (the region id's)
     bits8 disciplines[19];
     // Store the dice value for each tile to generate students
     bits8 diceValues[19];
     // Store each ARC grant as a graph (I'll explain, dw)
     ARCGrant grants[1000]; // 1000 is just an arbitrary number, can't be bothered finding the exact number of grants possible
     // Store each campus as an array with as many elements as there are vertices
     bits8 campuses[1000]; // 1000 is arbitrary, can't be bothered to count number of vertices
     // Store the IP patents were the relevent (wrong spelling i know) number is in (PLAYER_ID-1)
     int patents[3];
     // Similar as IP's, but just for publications
     int publications[3];
     // Store the resources (students) for each uni
     int resources[3][6];
 } game;

typedef struct _PLAYERResource {
    // Store amount of Resources
    Int resources;
    // Each individual resource system
    Int bT;
    Int bPS;
    Int bHTW;
    Int mJob;
    Int mTv;
    Int m$;

 } PLAYERResource;

typedef struct _PLAYERPoint {
    // Store amount of KPI Points
    Int keyPI;
    // Each individual point system
    Int campus;
    Int g08;
    Int arcGrant;
    Int mostArc;
    Int researchPub;
    Int intellectP;

 } PLAYERPoint;

