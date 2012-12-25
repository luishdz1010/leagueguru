#ifndef FILEPATHS_H
#define FILEPATHS_H

#include <QString>

class FilePaths
{
public:
    FilePaths() = delete;

    static void init();

    static const QString& sharedDataLocation()
    {
        return sharedData;
    }

private:
    static QString sharedData;
};

#endif // FILEPATHS_H
