#include <iostream>
#include <fstream>
#include <sstream>

#include "MongoUtil.h"
#include "clsRasterData.cpp"

#include "SubbasinIUHCalculator.h"

using namespace std;

void MainMongoDB(const char *modelStr, const char *gridFSName, int nSubbasins, const char *host, int port, int dt)
{
    // connect to mongodb
    MongoClient client = MongoClient(host, port);
    mongoc_gridfs_t *gfs = client.getGridFS(string(modelStr), string(gridFSName));
//    mongo conn[1];
//    gridfs gfs[1];
//    int status = mongo_connect(conn, host, port);
//
//    if (MONGO_OK != status)
//    {
//        cout << "can not connect to MongoDB.\n";
//        exit(-1);
//    }

//    gridfs_init(conn, modelStr, gridFSName, gfs);
	int subbasinStartID = 1;
	if (nSubbasins == 0) subbasinStartID = 0;
    for (int i = subbasinStartID; i <= nSubbasins; i++)
    {
        //cout << "subbasin: " << i << endl;
        //input
        ostringstream oss;
        string deltaName, streamLinkName, tName, maskName, landcoverName;
        oss << i << "_DELTA_S";
        deltaName = oss.str();

        oss.str("");
        oss << i << "_T0_S";
        tName = oss.str();

        oss.str("");
        oss << i << "_MASK";
        maskName = oss.str();

		oss.str("");
        oss << i << "_LANDCOVER";
        landcoverName = oss.str();

        clsRasterData<int> rsMask;
        rsMask.ReadFromMongoDB(gfs, maskName.c_str());

        clsRasterData<float> rsTime, rsDelta, rsLandcover;
        rsTime.ReadFromMongoDB(gfs, tName.c_str());
		rsDelta.ReadFromMongoDB(gfs, deltaName.c_str());
		rsLandcover.ReadFromMongoDB(gfs, landcoverName.c_str());

        SubbasinIUHCalculator iuh(dt, rsMask, rsLandcover, rsTime, rsDelta, gfs);
        iuh.calCell(i);
    }

    mongoc_gridfs_destroy(gfs);
}

int main(int argc, const char **argv)
{
    const char *host = argv[1];
    int port = atoi(argv[2]);
    const char *modelName = argv[3];
    const char *gridFSName = argv[4];
    int dt = atoi(argv[5]);
    int nSubbasins = atoi(argv[6]);

    MainMongoDB(modelName, gridFSName, nSubbasins, host, port, dt);

    cout << " IUH calculation is OK!" << endl;
    return 0;
}