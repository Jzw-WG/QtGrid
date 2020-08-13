#ifndef REPLAY_FILE_H
#define REPLAY_FILE_H


class ReplayFile
{
public:
    ReplayFile();
    char* fileName;
    char* creationDate;
    char* creationTime;
    char* recordType;
    char* fileLength;
    char* duration;
    char* deviceid;
    char* operatorid;
    char* workingMode;
};

#endif // REPLAY_FILE_H
