#ifndef EPIDEMIC_SIMULATOR_GRAPH_H
#define EPIDEMIC_SIMULATOR_GRAPH_H

#include "cinder/gl/gl.h"
#include "core/person.h"

typedef std::pair<epidemic_simulator::Status, ci::Rectf> ColumnStatus;
typedef std::pair<size_t, glm::vec2> LocatedLabel;
namespace epidemic_simulator {
/**
 * Visualizes the spread of a virus over time in a stacked bar chart format.
 */
class Graph {
 public:
  /**
   * Instantiates a new Graph instance.
   * @param width the width of the graph.
   * @param height the height of the graph.
   * @param number_people the number of people in the simulation.
   * @param initial_horizontal_label_interval the interval of labels for the
   * horizontal axis at the start of the simulation.
   */
  Graph(double width, double height, size_t number_people,
        size_t initial_horizontal_label_interval);

  /**
   * Adds a new day's worth of data to status_frequencies_.
   * @param frequencies a Map detailing how many people of each status should be
   * added to frequencies_ for the next day.
   */
  void AddDay(const std::map<Status, size_t>& frequencies);

  /**
   * Generates the bars in the graph based on the values in status_frequencies_
   * and adds them to bars_.
   */
  void GenerateBars();

  /**
   * Generates vertical labels for the graph and adds them to vertical_labels_.
   * This method only needs to be called once because the vertical labels will
   * remain unchanged after the Graph is instantiated. Their locations will be
   * relative to (0,0).
   * @param interval the interval of the vertical labels.
   */
  void GenerateVerticalLabels(size_t interval);

  /**
   * Generates horizontal labels for the graph based on horizontal_interval_ and
   * adds them to horizontal_labels_. Their locations will be relative to (0,0).
   * Updates horizontal_interval_ if the number of labels reach
   * kMaxNumberLabels.
   */
  void GenerateHorizontalLabels();

  const std::vector<ColumnStatus>& GetBars() const;
  const std::vector<LocatedLabel>& GetVerticalLabels() const;
  const std::vector<LocatedLabel>& GetHorizontalLabels() const;

 private:
  /** The frequency of each status for each day. **/
  std::map<Status, std::vector<size_t>> status_frequencies_;

  /** The height of the graph. **/
  double height_;

  /** The width of the graph **/
  double width_;

  std::vector<LocatedLabel> vertical_labels_;
  std::vector<LocatedLabel> horizontal_labels_;
  std::vector<ColumnStatus> bars_;
  size_t number_days_;
  size_t number_people_;
  size_t horizontal_interval_;

  /** Maximum number of horizontal labels for a graph to display at a time. **/
  static const size_t kMaxNumberLabels = 10;
};
}  // namespace epidemic_simulator

#endif  // EPIDEMIC_SIMULATOR_GRAPH_H
