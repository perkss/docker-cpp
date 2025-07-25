#include "search_images_cmd.hh"

namespace dockercpp::command {

SearchImagesCmdImpl::SearchImagesCmdImpl(std::unique_ptr<search::Exec> exec)
    : AbstrDockerCmd<SearchImagesCmd, std::vector<SearchItem>>(std::move(exec)),
      m_limit(0) {}

std::vector<SearchItem> SearchImagesCmdImpl::exec() {
  return m_execution->exec(shared_from_this());
}

std::string SearchImagesCmdImpl::getTerm() const {
    return m_term;
}

SearchImagesCmd& SearchImagesCmdImpl::withTerm(const std::string& term) {
    m_term = term;
    return *this;
}

int SearchImagesCmdImpl::getLimit() const {
    return m_limit;
}

SearchImagesCmd& SearchImagesCmdImpl::withLimit(int limit) {
    m_limit = limit;
    return *this;
}

}
