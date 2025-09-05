#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>
#include <sys/types.h>
#include <unordered_map>
#include <vector>


class Scale
{
public:
    static constexpr auto kScaleWeight = int32_t{1};

    constexpr Scale(std::string_view name, std::string_view left, std::string_view right) noexcept
        : id_{name},
          left_{left},
          right_{right}
    {}

    constexpr auto& id() const noexcept { return id_; }
    constexpr auto& left() const noexcept { return left_; }
    constexpr auto& right() const noexcept { return right_; }

    constexpr auto total_weight() const noexcept { return add_left_ + add_right_ + initial_; }
    constexpr auto added_weights() const noexcept { return std::make_tuple(add_left_, add_right_); }
    constexpr bool visited() const noexcept { return initial_ > 0; }

    constexpr void set_added_weights(int32_t left, int32_t right) noexcept
    {
        add_left_  = left;
        add_right_ = right;
    }

    constexpr void set_initial_weights(int32_t left, int32_t right) noexcept { initial_ = left + right + kScaleWeight; }

private:
    std::string id_;
    std::string left_;
    std::string right_;

    int32_t initial_   = 0;
    int32_t add_left_  = 0;
    int32_t add_right_ = 0;
};



class TreeOfScales
{
public:
    TreeOfScales() noexcept = default;

    void add_scale_entry(std::string_view name, std::string_view left, std::string_view right) noexcept
    {
        scales_.emplace_back(name, left, right);
    }

    auto balance_scales()
    {
        // If more than one traversal would be required, it would be better to build the tree where Scale contains
        // left/right ptrs instead. The same O(log N) per-node cost is necessary to balance the tree and build it with
        // ptrs.
        for(auto& scale: scales_)
            scale_map_.try_emplace(scale.id(), std::addressof(scale));

        for(auto& scale: scales_)
        {
            if(scale.visited())
                continue;
            rebalance_visitor_(scale.id());
        }
    }

    constexpr auto& scale_entries() const noexcept { return scales_; }

private:
    // Scale objects data owner (same order as input)
    std::vector<Scale> scales_{};

    // Pure ref-ref hash-map to get the Scale objects with names Scale::left() and Scale::right().
    std::unordered_map<std::string_view, Scale*> scale_map_{};

    int32_t rebalance_visitor_(std::string const& pan) const
    {
        bool const is_scale = std::isalpha(pan[0]);
        if(!is_scale)
            return std::stoi(pan);

        auto const it = scale_map_.find(pan);
        if(it == scale_map_.end())
            throw std::logic_error("missing scale in input");

        auto& scale = *(it->second);

        if(scale.visited())
            return scale.total_weight();

        auto const left_weight  = rebalance_visitor_(scale.left());
        auto const right_weight = rebalance_visitor_(scale.right());

        auto const add_left  = std::max(right_weight - left_weight, 0);
        auto const add_right = std::max(left_weight - right_weight, 0);

        scale.set_initial_weights(left_weight, right_weight);
        scale.set_added_weights(add_left, add_right);

        return scale.total_weight();
    }
};
