
#include <algorithm>
#include <iterator>
#include <map>
#include <string>
#include <vector>

struct rdf_options_type {
  size_t rdf_bins = 0;
  size_t rdf_wait = 0;
};
struct compression_options_type {
  bool compression = false;
  double density_final = 0;
  double density_inc = 0;
  bool reverse_comp = false;
  size_t compress_count = 0;
};

struct boundary_contions_options_type {
  /**
   * @brief An array of boundaries where the map holds the type
   * of the boundary, e.g. Reflective, HardWall,
   * while the 2d array holds the points for the 2D surface
   */
  std::vector<std::map<std::string, std::vector<std::vector<double>>>> bc;
};

struct test_options_type {
  bool is_testing = false;  // fixes the seed for regression testing
};

struct options_type {
  std::string dir = ".";             // file output directory
  std::string simulation_type = "";  // type of simulation e.g. NormalRun
  std::string simulation_name = "";  // simulation prefix/ name
  std::string potential_type = "";   // pair potential type
  std::string stepping_alg = "";     // iterative algorithm of particles
  std::string lattice = "";          // lattice formation
  bool visualise = false;            // save all positions, of all particles
  std::vector<size_t> particles;     // number of particles in each axis
  double random_lattice_var = 0;     // variance of dist for random lattice
  size_t steps = 2000;               // number of total iterations
  size_t Nx, Ny, Nz, N = 0;          // Particles in the x, y, z and total
  double Lx, Ly, Lz, L = 0;          // Individual box lengths
  double volume = 0;                 // volume of the box
  double dt = 0.005;                 // timestep
  bool normalise_dt_w_temp = true;   // normalise the timestep with T0
  double density = 0.5;              // density
  double target_temperature = 0;     // target/ Thermostat temperature
  double temperature = 0;            // simulation temperature
  double power = 0;                  // pair potential intensity
  double a_cst = 0;                  // generic softening parameter
  double kinetic_energy = 0;         // kinetic energy
  double cut_off = 0;                // cut off radius of simulation
  double scale_v = 0;                // velocity scaling

  rdf_options_type rdf_options;
  compression_options_type compression_options;
  test_options_type test_options;

  // // Default constructor
  // options_type();
  // // Copy constructor
  // options_type(const options_type &copy);
};

struct vector_3d {
  std::vector<double> x;
  std::vector<double> y;
  std::vector<double> z;

  vector_3d(std::vector<double> x_in = {0}, std::vector<double> y_in = {0},
            std::vector<double> z_in = {0}) {
    x.swap(x_in);
    y.swap(y_in);
    z.swap(z_in);
  }

  vector_3d(size_t x_size, size_t y_size, size_t z_size) {
    x.resize(x_size);
    y.resize(y_size);
    z.resize(z_size);
  }
  vector_3d(size_t size) : vector_3d(size, size, size) {}

  inline vector_3d operator=(const vector_3d& a) {
    x = a.x;
    y = a.y;
    z = a.z;
    return *this;
  }

  inline vector_3d operator+(const vector_3d& a) const {
    vector_3d temp(a.x.size(), a.y.size(), a.z.size());
    std::transform(x.begin(), x.end(), a.x.begin(), temp.x.begin(),
                   std::plus<double>());
    std::transform(y.begin(), y.end(), a.y.begin(), temp.y.begin(),
                   std::plus<double>());
    std::transform(z.begin(), z.end(), a.z.begin(), temp.z.begin(),
                   std::plus<double>());
    return vector_3d(temp);
  }

  inline vector_3d operator-(const vector_3d& a) const {
    vector_3d temp(a.x.size(), a.y.size(), a.z.size());
    std::transform(x.begin(), x.end(), a.x.begin(), temp.x.begin(),
                   std::minus<double>());
    std::transform(y.begin(), y.end(), a.y.begin(), temp.y.begin(),
                   std::minus<double>());
    std::transform(z.begin(), z.end(), a.z.begin(), temp.z.begin(),
                   std::minus<double>());
    return vector_3d(temp);
  };

  inline vector_3d operator*(const vector_3d& a) const {
    vector_3d temp(a.x.size(), a.y.size(), a.z.size());
    std::transform(x.begin(), x.end(), a.x.begin(), temp.x.begin(),
                   std::multiplies<double>());
    std::transform(y.begin(), y.end(), a.y.begin(), temp.y.begin(),
                   std::multiplies<double>());
    std::transform(z.begin(), z.end(), a.z.begin(), temp.z.begin(),
                   std::multiplies<double>());
    return vector_3d(temp);
  }

  inline vector_3d operator/(const vector_3d& a) const {
    vector_3d temp(a.x.size(), a.y.size(), a.z.size());
    std::transform(x.begin(), x.end(), a.x.begin(), temp.x.begin(),
                   std::divides<double>());
    std::transform(y.begin(), y.end(), a.y.begin(), temp.y.begin(),
                   std::divides<double>());
    std::transform(z.begin(), z.end(), a.z.begin(), temp.z.begin(),
                   std::divides<double>());
    return vector_3d(temp);
  }
};

struct point_3d {
  double x;
  double y;
  double z;

  point_3d(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

  inline point_3d operator=(const point_3d& a) {
    x = a.x;
    y = a.y;
    z = a.z;
    return *this;
  }

  inline point_3d operator+(const point_3d& a) const {
    return point_3d(x + a.x, y + a.y, z + a.z);
  }

  inline point_3d operator-(const point_3d& a) const {
    return point_3d(x - a.x, y - a.y, z - a.z);
  };

  inline point_3d operator*(const point_3d& a) const {
    return point_3d(x * a.x, y * a.y, z * a.z);
  }

  inline point_3d operator/(const point_3d& a) const {
    return point_3d(x / a.x, y / a.y, z / a.z);
  }
};