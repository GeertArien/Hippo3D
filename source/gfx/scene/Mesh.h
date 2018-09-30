#pragma once

#include <vector>

namespace Mantis {

	namespace GFX {

		class Mesh final {

		public:
			using unit = float;

			Mesh() = default;

			explicit Mesh(const std::vector<unit>& vertice_data);

			explicit Mesh(std::vector<unit>&& vertice_data);

			Mesh(std::initializer_list<unit> vertice_data);

			unsigned int GetID() const { return id_; }

			const float* GetDataPointer() const noexcept { return vertice_data_.data(); }

			const size_t GetDataSize() const noexcept { return vertice_data_.size() * sizeof(unit); }

		private:
			unsigned int id_ = 0;
			std::vector<unit> vertice_data_;

		};

	}
}

