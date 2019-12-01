#include "ValidationResult.hpp"

#include <unordered_set>
#include <string>
#include <sstream>
#include <ostream>
#include <functional>
#include <iterator>

namespace Slic3r {

namespace
{

// Helper method to concatenate all strings in a vector.
// Newline included between each.
// Each run through internationalization to be translated.
std::string concatenate(const std::unordered_set<std::string>& strings,
    const ValidationResult::TranslateStdStringFn& translate)
{
    std::ostringstream oss;
    for (auto it = strings.cbegin(); it != strings.cend(); )
    {
        // Translate and add to the output stream
        if (translate)
        {
            oss << translate(*it);
        }
        else
        {
            oss << *it;
        }
        // Put a newline between each but not at the end of the list
        if (++it != strings.cend())
        {
            oss << std::endl;
        }
    }
    return oss.str();
}

}  // namespace


std::string ValidationResult::get_errors_concatenated(const ValidationResult::TranslateStdStringFn& translate) const
{
    return concatenate(errors, translate);
}

std::string ValidationResult::get_warnings_concatenated(const ValidationResult::TranslateStdStringFn& translate) const
{
    return concatenate(errors, translate);
}

std::string ValidationResult::get_errors_and_warnings_concatenated(const ValidationResult::TranslateStdStringFn& translate) const
{
    std::ostringstream oss;
    oss << concatenate(errors, translate);
    // Only insert newlines separating errors and warnings if there were both errors and warnings
    if (!errors.empty() && !warnings.empty())
        oss << std::endl << std::endl;
    oss << concatenate(warnings, translate);
    return oss.str();
}

bool ValidationResult::empty() const
{
    return errors.empty() && warnings.empty();
}

void ValidationResult::clear()
{
    errors.clear();
    warnings.clear();
}

void ValidationResult::append(ValidationResult&& other)
{
    errors.insert(std::make_move_iterator(other.errors.begin()),
                  std::make_move_iterator(other.errors.end()));
    warnings.insert(std::make_move_iterator(other.warnings.begin()),
                    std::make_move_iterator(other.warnings.end())); 
}

}  // namespace Slic3r
