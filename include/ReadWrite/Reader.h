#include <Math/Vector3.hpp>
#include <Math/Matrix3.hpp>
#include <Light/Normal.hpp>
#include <ReadWrite/Object.h>


#ifndef KGG_CPP_PROJECT_REPO_READER_H
#define KGG_CPP_PROJECT_REPO_READER_H

class Reader {
public:
    Object Read(const std::string filename);
};


#endif