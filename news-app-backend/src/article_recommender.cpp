// recommendation_model.cpp

/**
 * Convert each title to TF-IDF vectors and then do cosine similarity on them
 *
 *
 * For each word t in the title d from a collection of titles D:
 *  calculate TF(t, d) = num times t appears in d / num words in d
 *  then calculate IDF(t, D) = log(|D| / num titles containing t)
 *
 * The resulting TF-IDF score for the word t is TF(t, d) * IDF(t, D).
 *
 * We can construct TF-IDF score vectors for each title and then perform
 * a cosine similarity calculation between the two vectors to measure
 * their similarity.
 */

#include "article_recommender.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

ArticleRecommender::ArticleRecommender(const std::vector<std::string> &titles)
{
    D = titles.size();
    cleanedWordCounts = std::vector<Title>{};
    for (int i = 0; i < D; ++i)
    {
        std::vector<std::string> words = cleanSplitTitle(titles[i]);
        std::map<std::string, int> counts;
        for (int i = 0; i < words.size(); ++i)
        {
            ++counts[words[i]];
            ++overallWordCounts[words[i]];
        }
        cleanedWordCounts.push_back({counts, words.size()});
    }
}

std::vector<TITLE_MATRIX> ArticleRecommender::calculateTFIDF()
{
    std::vector<TITLE_MATRIX> out;
    for (Title &title : cleanedWordCounts)
    {
        out.push_back(vectorize(title));
    }
    return out;
}

std::vector<std::string> ArticleRecommender::cleanSplitTitle(const std::string &input)
{
    boost::regex pattern("[^a-zA-Z\\s]");
    std::string result = boost::regex_replace(input, pattern, "");
    boost::algorithm::to_lower(result);
    std::vector<std::string> words;
    boost::split(words, result, boost::is_any_of(" "));
    return words;
}

TITLE_MATRIX ArticleRecommender::vectorize(const std::string &title)
{
    std::vector<std::string> words = cleanSplitTitle(title);
    std::map<std::string, int> counts;
    for (int i = 0; i < words.size(); ++i)
    {
        ++counts[words[i]];
    }

    return vectorize(Title{counts, words.size()});
}

TITLE_MATRIX ArticleRecommender::vectorize(const Title &title)
{

    TITLE_MATRIX titleMat(1, title.counts.size());
    int i = 0;
    std::cout << "D: " << D << std::endl;
    for (auto [word, count] : title.counts)
    {
        double tf = (double)count / title.d;
        std::cout << overallWordCounts[word] + 1 << " " << (D / (overallWordCounts[word] + 1)) << std::endl;
        double idf = log((double)D / (overallWordCounts[word] + 1));
        std::cout << "Word: " << word << ", TF: " << tf << ", IDF: " << idf << std::endl;
        titleMat(0, i) = tf * idf;
        ++i;
    }
    return titleMat;
}

TITLE_MATRIX ArticleRecommender::getSimilarity(const std::string &a)
{
    TITLE_MATRIX out(1, D);
    TITLE_MATRIX score = vectorize(a);
    for (int i = 0; i < D; ++i)
    {
        TITLE_MATRIX currMat = vectorize(cleanedWordCounts[i]);
        double similarity = cosineSimilarity(score, currMat);
        printf("Similarity with title %d: %.6f\n", i + 1, similarity);
        out(0, i) = similarity;
    }
    return out;
}

double ArticleRecommender::cosineSimilarity(TITLE_MATRIX A, TITLE_MATRIX B)
{
    size_t aSize = A.size();
    size_t bSize = B.size();

    if (aSize < bSize)
    {
        A.reshape(1, bSize);
    }
    else if (bSize > aSize)
    {
        B.reshape(1, aSize);
    }

    return norm_dot(A, B);
}
