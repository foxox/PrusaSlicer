#ifndef slic3r_ValidationResult_hpp_
#define slic3r_ValidationResult_hpp_

#include <unordered_set>
#include <string>
#include <functional>

namespace Slic3r {

// Encapsulates errors and warnings that can result from validating configurations.
struct ValidationResult
{
    // Translation function type taking an std::string as input and producing an std::string as output.
    using TranslateStdStringFn = std::function<std::string(const std::string&)>;

    // Returns all errors concatenated as one string. Newlines separate each.
    // If a translation function is provided, each message gets translated individually.
    std::string get_errors_concatenated(const TranslateStdStringFn& translate = {}) const;

    // Returns all warnings concatenated as one string. Newlines separate each.
    // If a translation function is provided, each message gets translated individually.
    std::string get_warnings_concatenated(const TranslateStdStringFn& translate = {}) const;

    // Returns all errors and warnings concatenated as one string.
    // Errors come first, then warnings. All separated by newline delimiters.
    // If a translation function is provided, each message gets translated individually.
    std::string get_errors_and_warnings_concatenated(const TranslateStdStringFn& translate = {}) const;

    // Returns whether there are any errors or there are any warnings.
    // True if there are both no errors and no warnings, false if there is any warning or error.
    bool empty() const;

    // Clears out both the errors and warnings.
    void clear();

    // Appends the contents of another ValidationResult to this one.
    void append(ValidationResult&& other);

    // Error message strings.
    // It is expected that these will be pre-translation strings which can be run through I18N later.
    std::unordered_set<std::string> errors;

    // Warning message strings.
    // It is expected that these will be pre-translation strings which can be run through I18N later.
    std::unordered_set<std::string> warnings;
};

}

#endif /* slic3r_ValidationResult_hpp_ */
