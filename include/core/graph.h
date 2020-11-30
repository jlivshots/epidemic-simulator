#ifndef EPIDEMIC_SIMULATOR_GRAPH_H
#define EPIDEMIC_SIMULATOR_GRAPH_H

#include "cinder/gl/gl.h"
#include "core/person.h"

typedef std::pair<epidemic_simulator::Status,ci::Rectf> ColumnStatus;
typedef std::pair<size_t , glm::vec2> LocatedLabel;
namespace epidemic_simulator {
class Graph {
 public:
  Graph(double width, double height, size_t number_people);
  void AddDay(const std::map<Status, size_t>& frequencies);
  void GenerateBars();
  void GenerateVerticalLabels(size_t number_labels);
  void GenerateHorizontalLabels();
  const std::vector<ColumnStatus>& GetBars() const;
  const std::vector<LocatedLabel>& GetVerticalLabels() const;
  const std::vector<LocatedLabel>& GetHorizontalLabels() const;


 private:
  std::map<Status, std::vector<size_t>> status_frequencies_;
  std::vector<LocatedLabel> vertical_labels_;
  std::vector<LocatedLabel> horizontal_labels_;
  std::vector<ColumnStatus> bars_;
  size_t number_days_;
  size_t number_people_;
  double height_;
  double width_;
  std::vector<Status> kVerticalOrder = {Status::Vulnerable, Status::Immune,
                                        Status::Incubating, Status::Infectious};

};
}  // namespace epidemic_simulator

#endif  // EPIDEMIC_SIMULATOR_GRAPH_H
