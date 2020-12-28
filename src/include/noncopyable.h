//
// Created by tracy on 2020/12/28.
//

#ifndef COMPUTERGRAPHICSEXERCISE_NONCOPYABLE_H
#define COMPUTERGRAPHICSEXERCISE_NONCOPYABLE_H

namespace cg {
class NonCopyable {
public:
    NonCopyable(const NonCopyable &) = delete;
    void operator=(const NonCopyable &) = delete;

protected:
    NonCopyable() = default;
    ~NonCopyable() = default;
};
}  // namespace cg
#endif  // COMPUTERGRAPHICSEXERCISE_NONCOPYABLE_H
