## Technical details
LeagueGuru is coded in C++/11 and makes use of various GPL libraries like Boost, QT Open Source and Google's Protobuf. While end-users see only a tiny client with the provided features, LeagueGuru is made of a few tools that in conjunction create the whole experience. 

### Crawler
LeagueGuru uses real time champion data in order to generate the best picks for a given user situation, this data is gathered from popular sites like lolking.com or championselect.net. The GuruCrawler data-mines those sites and generates a graph containing the relationships between all the champions in the league, this graph is then serialized into a single file. This tool is not shipped in the current release.

### Server
The GuruServer parses the stats graph and client requests in order to filter the best picks, we wanted to separate the whole system into a client/server architecture because in this way clients doesn't have to be aware of current champion statistics. Currently, the server is shipped with the official release. The graph file is updated by the GuruClient in a weekly basis from a Dropbox source.

### Client
The GuruClient is in charge of receiving input from the user and the LoL client, it sends relevant data to a GuruServer instance (a local one in the current release) in order to generate picks/bans suggestions. Although the client is not complex per se, its way larger in code size due to the nature of the tasks it performs. New champions and portrait updates are downloaded from Dropbox as soon as they became available.

This repo contains only the GuruClient source code.

## Current work
Currently we are looking into ways to make the UI easier to use and understand, we are polishing the pick suggestions algorithms (in the private GuruServer repo) and, as a mid-term priority, finding new ways to obtain data from the LoL client without violating its ToS agreement.
