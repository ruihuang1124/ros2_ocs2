/******************************************************************************
Copyright (c) 2020, Farbod Farshidian. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#include "ocs2_ros_interfaces/synchronized_module/RosReferenceManager.h"

#include "ocs2_ros_interfaces/common/RosMsgConversions.h"
#include "rclcpp/rclcpp.hpp"

// MPC messages
#include <ocs2_msgs/msg/mode_schedule.hpp>
#include <ocs2_msgs/msg/mpc_target_trajectories.hpp>

namespace ocs2 {
    RosReferenceManager::RosReferenceManager(
        std::string topicPrefix,
        std::shared_ptr<ReferenceManagerInterface> referenceManagerPtr)
        : ReferenceManagerDecorator(std::move(referenceManagerPtr)),
          topic_prefix_(std::move(topicPrefix)) {
    }


    void RosReferenceManager::subscribe(const rclcpp::Node::SharedPtr &node) {
        // ModeSchedule
        auto modeScheduleCallback = [this](const ocs2_msgs::msg::ModeSchedule &msg) {
            auto modeSchedule = ros_msg_conversions::readModeScheduleMsg(msg);
            referenceManagerPtr_->setModeSchedule(std::move(modeSchedule));
        };
        mode_schedule_subscriber_ =
                node->create_subscription<ocs2_msgs::msg::ModeSchedule>(
                    topic_prefix_ + "_mode_schedule", 1, modeScheduleCallback);

        // TargetTrajectories
        auto targetTrajectoriesCallback =
                [this](const ocs2_msgs::msg::MpcTargetTrajectories &msg) {
            auto targetTrajectories =
                    ros_msg_conversions::readTargetTrajectoriesMsg(msg);
            referenceManagerPtr_->setTargetTrajectories(
                std::move(targetTrajectories));
        };
        target_trajectories_subscriber_ =
                node->create_subscription<ocs2_msgs::msg::MpcTargetTrajectories>(
                    topic_prefix_ + "_mpc_target", 1, targetTrajectoriesCallback);
    }

    void RosReferenceManager::subscribe(const rclcpp_lifecycle::LifecycleNode::SharedPtr &node) {
        auto modeScheduleCallback = [this](const ocs2_msgs::msg::ModeSchedule &msg) {
            auto modeSchedule = ros_msg_conversions::readModeScheduleMsg(msg);
            referenceManagerPtr_->setModeSchedule(std::move(modeSchedule));
        };
        mode_schedule_subscriber_ =
                node->create_subscription<ocs2_msgs::msg::ModeSchedule>(
                    topic_prefix_ + "_mode_schedule", 1, modeScheduleCallback);

        // TargetTrajectories
        auto targetTrajectoriesCallback =
                [this](const ocs2_msgs::msg::MpcTargetTrajectories &msg) {
            auto targetTrajectories =
                    ros_msg_conversions::readTargetTrajectoriesMsg(msg);
            referenceManagerPtr_->setTargetTrajectories(
                std::move(targetTrajectories));
        };
        target_trajectories_subscriber_ =
                node->create_subscription<ocs2_msgs::msg::MpcTargetTrajectories>(
                    topic_prefix_ + "_mpc_target", 1, targetTrajectoriesCallback);
    }
} // namespace ocs2
