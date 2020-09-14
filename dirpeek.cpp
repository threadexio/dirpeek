#include <iostream>
#include <fstream>
#include <cpr/cpr.h>
#include <vector>
#include <thread>
#include <algorithm>
#include <boost/program_options.hpp>
using namespace std;
namespace po = boost::program_options;

int Get(string url)
{
    return cpr::Get(cpr::Url{url.c_str()}).status_code;
}

string trim (string x)
{
    if (x[0] == ' ')
    {
        x.erase(0, 1);
    }
    if (x[x.length() - 1] == ' ')
    {
        x.erase(x.length() - 1, x.length());
    }
    return x;
}

vector<string> split(string text, char sep)
{
    vector<string> tokens;
    tokens.push_back(" ");
    if (text == "-")
    {
        return tokens;
    }
    size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != string::npos)
    {
        tokens.push_back("." + text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back("." + text.substr(start));
    return tokens;
}

void dirbust(string host, vector<string> list, int start, int offset, int lines, vector<string> exts)
{
    for (int i = start; i <= list.size();)
    {
        for (int u = 0; u < exts.size(); u++)
        {
            string url = trim((host + "/" + list[i] + exts[u]));
            int r = Get(url);
            if (r == 404)
            {
                continue;
            }
            else if (r == 0)
            {
                continue;
            }
            else
            {
                cout << " | " << list[i] << exts[u] << " (Status: \033[1m" << r << "\033[0m)\n";
            }
        }
        if (i + offset >= lines)
        {
            break;
        }
        i += offset;
    }
}

int main(int argc, char *argv[])
{
    int threadNum;             // number of threads
    vector<thread> threadPool; // thread vector

    string host;     // Host string
    string wordlist; // Wordlist string

    vector<string> list;       // Wordlist vector
    vector<string> extensions; // Extension vector

    cout << "\n\t      Yet Another\n"                      //
         << "\t    Directory Buster\n\n"                   //
         << "\tBy threadexio on Github\n"                  //  The header
         << "     https://github.com/threadexio\n"         //
         << "_______________________________________\n\n"; //

    po::options_description desc("Flags");
    desc.add_options()("help,h", "This help message")("threads,t", po::value<int>(&threadNum)->default_value(10), "Theads to use")("url,u", po::value<string>(&host), "Url to test")("wordlist,w", po::value<string>(&wordlist), "Wordlist to use")("extensions,x", po::value<string>(), "Extensions to use");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    // Check if the flag help is set
    if (vm.count("help"))
    {
        cout << desc << "\n";
        return 1;
    }

    // Check if the url and wordlist flags are set
    if (!vm.count("url") || !vm.count("wordlist"))
    {
        cout << "Flags -u and -w are required\n";
        return 2;
    }

    // Check if any extensions were given
    if (vm.count("extensions"))
    {
        extensions = split(vm["extensions"].as<string>(), ',');
    }
    else
    {
        extensions.push_back("/");
    }

    // The stuff under the header
    cout << "\n\033[94m[*]\033[0m Threads: " << threadNum;
    cout << "\n\033[94m[*]\033[0m Host: " << host;
    cout << "\n\033[94m[*]\033[0m Extensions: ";
    for (int i = 0; i < extensions.size(); i++)
    {
        cout << extensions[i] << " ";
    }
    cout << "\n_______________________________________\n";

    // Read the wordlist into a vector for later use
    ifstream file(wordlist);
    if (file.is_open())
    {
        for (string line; file >> line;)
        {
            if (line != "")
            {
                list.push_back(line);
            }
        }
        file.close();
    }
    else
    {
        cout << "Could not read file\n";
        return 1;
    }

    // Check if there are more threads than lines
    if (threadNum > list.size())
    {
        cout << "Cannot have more threads than lines\n";
        return 3;
    }

    cout << "\n\033[92m[+]\033[0m " << host << endl;

    // Populate the thread pool and start
    for (int i = 0; i < threadNum; i++)
    {
        threadPool.push_back(thread(dirbust, host, list, i, threadNum, list.size(), extensions));
    }

    // Wait for the threads to exit
    for_each(threadPool.begin(), threadPool.end(), mem_fn(&thread::join));

    cout << " |_\n";
}