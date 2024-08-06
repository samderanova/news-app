#ifndef RECOMMENDATION_MODEL_HPP
#define RECOMMENDATION_MODEL_HPP

#define MLPACK_PRINT_INFO
#define MLPACK_PRINT_WARN

#include <map>
#include <string>
#include <vector>

#include <mlpack.hpp>

#define TITLE_MATRIX arma::Mat<double>

class ArticleRecommender
{

  public:
    ArticleRecommender(const std::vector<std::string> &titles);

    std::vector<TITLE_MATRIX> calculateTFIDF();
    TITLE_MATRIX getSimilarity(const std::string &input);

  private:
    struct Title
    {
        std::map<std::string, int> counts;
        size_t d;
    };

    size_t D;

    std::vector<std::string> cleanSplitTitle(const std::string &input);
    double cosineSimilarity(TITLE_MATRIX A, TITLE_MATRIX B);

    TITLE_MATRIX vectorize(const Title &title);
    TITLE_MATRIX vectorize(const std::string &input);

    std::map<std::string, unsigned int> countWords(const std::string &input);

    std::vector<Title> cleanedWordCounts;
    std::map<std::string, int> overallWordCounts;
};

#endif
