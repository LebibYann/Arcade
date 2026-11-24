/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** Test
** Minimal test framework, so the tests need no extra dependency.
*/

#pragma once

#include <exception>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace test
{
    struct Failure {
        std::string message;
    };

    struct Skip {
        std::string reason;
    };

    struct Case {
        std::string name;
        std::function<void()> body;
    };

    inline std::vector<Case> &registry(void)
    {
        static std::vector<Case> cases;
        return (cases);
    }

    struct Register {
        Register(const std::string &name, std::function<void()> body)
        {
            registry().push_back({name, body});
        }
    };

    /**
     ** @brief Run every registered test and print one line per test.
     **
     ** @return 0 if no test failed, 1 otherwise.
     */
    inline int runAll(std::ostream &out = std::cout)
    {
        int passed = 0;
        int failed = 0;
        int skipped = 0;

        for (const Case &test : registry()) {
            // Written first, so that a crash shows which test was running
            out << "  " << test.name << " ... " << std::flush;
            try {
                test.body();
                out << "PASS" << std::endl;
                ++passed;
            } catch (const Skip &skip) {
                out << "SKIP (" << skip.reason << ")" << std::endl;
                ++skipped;
            } catch (const Failure &failure) {
                out << "FAIL\n      " << failure.message << std::endl;
                ++failed;
            } catch (const std::exception &error) {
                out << "FAIL\n      exception: " << error.what() << std::endl;
                ++failed;
            }
        }
        out << passed << " passed, " << failed << " failed, " << skipped << " skipped" << std::endl;
        return (failed == 0 ? 0 : 1);
    }
}

#define TEST(name) \
    static void name(void); \
    static test::Register register_##name(#name, name); \
    static void name(void)

#define CHECK(condition) \
    do { \
        if (!(condition)) \
            throw test::Failure{std::string(__FILE__) + ":" + \
                std::to_string(__LINE__) + ": CHECK(" #condition ") failed"}; \
    } while (0)

#define CHECK_EQ(actual, expected) \
    do { \
        auto actualValue_ = (actual); \
        auto expectedValue_ = (expected); \
        if (!(actualValue_ == expectedValue_)) { \
            std::ostringstream message_; \
            message_ << __FILE__ << ":" << __LINE__ << ": " #actual " is " \
                << actualValue_ << ", expected " << expectedValue_; \
            throw test::Failure{message_.str()}; \
        } \
    } while (0)

#define SKIP(reason) throw test::Skip{reason}
