#pragma once

#include <vector>

namespace Mantis {

	class Mesh final {

	public:
		using unit = float;

		Mesh() = default;
		explicit Mesh(const std::vector<unit>& vertice_data);
		explicit Mesh(std::vector<unit>&& vertice_data);
		explicit Mesh(std::initializer_list<unit> vertice_data);

		const float* GetDataPointer() const noexcept
		{ return vertice_data_.data(); }

		const float GetDataSize() const noexcept
		{ return vertice_data_.size() * sizeof(unit); }

	private:
		std::vector<unit> vertice_data_;

	};

}

