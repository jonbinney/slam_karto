/*
 * Copyright 2010 SRI International
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KARTO_SPASOLVER_H
#define KARTO_SPASOLVER_H

#include <open_karto/Mapper.h>

#ifndef EIGEN_USE_NEW_STDVECTOR
#define EIGEN_USE_NEW_STDVECTOR
#endif // EIGEN_USE_NEW_STDVECTOR

#define EIGEN_DEFAULT_IO_FORMAT Eigen::IOFormat(10)
#include <Eigen/Eigen>

#include <sparse_bundle_adjustment/spa2d.h>
#include <slam_karto/slam_solver.h>

typedef std::vector<karto::Matrix3> CovarianceVector;

namespace karto_plugins
{
  class SPASolver : public karto::SLAMSolver 
  {
  public:
    SPASolver();
    virtual ~SPASolver();

  public:
    virtual void Clear();
    virtual void Compute();
    virtual const karto::ScanSolver::IdPoseVector& GetCorrections() const;

    virtual void AddNode(karto::Vertex<karto::LocalizedRangeScan>* pVertex);
    virtual void AddConstraint(karto::Edge<karto::LocalizedRangeScan>* pEdge);
 
    virtual void publishGraphVisualization(visualization_msgs::MarkerArray &marray);

  private:
    // Get the underlying graph from SBA
    // return the graph of constraints
    /// x,y -> x',y'   4 floats per connection

    karto::ScanSolver::IdPoseVector corrections;
    void getGraph(std::vector<float> &g) { m_Spa.getGraph(g); }

    sba::SysSPA2d m_Spa;
    int marker_count_;
  };
};

#endif // KARTO_SPASOLVER_H

