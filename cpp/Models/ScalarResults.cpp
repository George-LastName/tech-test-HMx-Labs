#include "ScalarResults.h"
#include <stdexcept>

ScalarResults::~ScalarResults() = default;

std::optional<ScalarResult> ScalarResults::operator[](const std::string& tradeId) const {
    if (!containsTrade(tradeId)) {
        return std::nullopt;
    }

    std::optional<double> priceResult = std::nullopt;
    std::optional<std::string> error = std::nullopt;

    auto resultIt = results_.find(tradeId);
    if (resultIt != results_.end()) {
        priceResult = resultIt->second;
    }

    auto errorIt = errors_.find(tradeId);
    if (errorIt != errors_.end()) {
        error = errorIt->second;
    }

    return ScalarResult(tradeId, priceResult, error);
}

bool ScalarResults::containsTrade(const std::string& tradeId) const {
    return results_.find(tradeId) != results_.end() || errors_.find(tradeId) != errors_.end();
}

void ScalarResults::addResult(const std::string& tradeId, double result) {
    results_[tradeId] = result;
}

void ScalarResults::addError(const std::string& tradeId, const std::string& error) {
    errors_[tradeId] = error;
}

ScalarResults::Iterator::Iterator(ScalarResults::Iterator::result_it res_start,
                                  ScalarResults::Iterator::result_it res_finish,
                                  ScalarResults::Iterator::error_it  err_start,
                                  ScalarResults::Iterator::error_it  err_finish)
                            : results_begin_(res_start), results_end_(res_finish),
                              errors_begin_(err_start), errors_end_(err_finish){

}


ScalarResults::Iterator& ScalarResults::Iterator::operator++() {
    if (results_begin_ != results_end_){
        ++results_begin_;
    } else if (errors_begin_ != errors_end_){
        ++errors_begin_;
    } else {
        throw std::runtime_error("Iterator::operator++() end of both maps");
    }
    return *this;
}

ScalarResult ScalarResults::Iterator::operator*() const {
    std::optional<double> priceResult = std::nullopt;
    std::optional<std::string> error = std::nullopt;
    std::string tradeId;


    if (results_begin_ != results_end_) {
        tradeId = results_begin_->first;
        priceResult = results_begin_->second;
    } else if (errors_begin_ != errors_end_) {
        tradeId = errors_begin_->first;
        error= errors_begin_->second;
    } else {
        throw std::runtime_error("Iterator::operator*() end of both maps");
    }

    return ScalarResult(tradeId, priceResult, error);
}

bool ScalarResults::Iterator::operator!=(const Iterator& other) const {
    return !(results_begin_ == other.results_begin_ && errors_begin_ == other.errors_begin_);
}

ScalarResults::Iterator ScalarResults::begin() const {
    return ScalarResults::Iterator(results_.begin(), results_.end(),
                                   errors_.begin(), errors_.end());
}

ScalarResults::Iterator ScalarResults::end() const {
    return ScalarResults::Iterator(results_.end(), results_.end(),
                                   errors_.end(), errors_.end());
}
