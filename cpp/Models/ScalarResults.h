#ifndef SCALARRESULTS_H
#define SCALARRESULTS_H
#include "IScalarResultReceiver.h"
#include "ScalarResult.h"
#include <map>
#include <optional>
#include <string>
#include <iterator>
#include <mutex>
#include <tuple>
#include <cstddef>

class ScalarResults : public IScalarResultReceiver {
public:
    std::optional<ScalarResult> operator[](const std::string& tradeId) const;

    bool containsTrade(const std::string& tradeId) const;

    void addResult(const std::string& tradeId, double result) override;

    void addError(const std::string& tradeId, const std::string& error) override;

    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = ScalarResult;
        using difference_type = std::ptrdiff_t;
        using pointer = ScalarResult*;
        using reference = ScalarResult&;

        using result_it = std::map<std::string, double>::const_iterator;
        using error_it = std::map<std::string, std::string>::const_iterator;

        Iterator(result_it res_start, result_it res_finish, error_it err_start, error_it err_finish);

        // Iterator must be constructable from ScalarResults parent
        Iterator& operator++();
        ScalarResult operator*() const;
        bool operator!=(const Iterator& other) const;
    private:
        result_it results_begin_;
        result_it results_end_;
        error_it  errors_begin_;
        error_it  errors_end_;
        // Returns true values if iterators are not at end. <results, errors>
        std::tuple<bool, bool> GetProgress() const;
    };

    Iterator begin() const;
    Iterator end() const;

private:
    std::map<std::string, double> results_;
    std::map<std::string, std::string> errors_;
    std::mutex mutex_;
};

#endif // SCALARRESULTS_H
