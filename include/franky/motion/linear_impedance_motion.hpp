#pragma once

#include <map>
#include <optional>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "franky/motion/impedance_motion.hpp"


namespace franky {
  class LinearImpedanceMotion : public ImpedanceMotion {
  public:
    struct Params : public ImpedanceMotion::Params {
      bool return_when_finished{true};
      double finish_wait_factor{1.2}; // Wait a bit longer to stop
    };

    explicit LinearImpedanceMotion(const Affine &target, double duration);

    explicit LinearImpedanceMotion(const Affine &target, double duration, const Params &params);

  protected:
    void initImpl(const franka::RobotState &robot_state, double time) override;

    std::tuple<Affine, bool>
    update(const franka::RobotState &robot_state, franka::Duration time_step, double time) override;

  private:
    Affine initial_pose_;
    double motion_init_time_{};
    double duration_;
    Params params_;
  };
} // namespace franky