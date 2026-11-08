// The music library's cue (0x105DC6A0 - 0x105DD580): the entity that holds the grid of cells of its parts and
// layers.
#include "code/music/cue.h"
#include "code/core/hash.h"

namespace music
{
	// The object around a tree node of the parts or layers (the nodes sit 0x1C bytes into the objects)
	template<class T> __forceinline T* ObjectOf(om::TreeNode* node)
	{
		T* result;
		if (node != 0)
		{
			result = reinterpret_cast<T*>(reinterpret_cast<char*>(node) - 0x1C);
		}
		else
		{
			result = 0;
		}
		return result;
	}
}

namespace om
{
	unsigned int Min(const unsigned int& first, const unsigned int& second);

	template<class T> bool TreeHead::InsertByIndex(T* object)
	{
		TreeNode* inserted = object != 0 ? &object->node : 0;
		TreeNode* parent = &nil;
		TreeNode* current = root;
		if (current != &nil)
		{
			do
			{
				parent = current;
				T* other = music::ObjectOf<T>(current);
				int difference = object->index - other->index;
				if (difference < 0)
				{
					current = current->left;
				}
				else if (difference > 0)
				{
					current = current->right;
				}
				else
				{
					return false;
				}
			}
			while (current != &nil);
		}
		inserted->parent = parent;
		if (parent == &nil)
		{
			root = inserted;
		}
		else
		{
			T* other = music::ObjectOf<T>(parent);
			int difference = object->index - other->index;
			if (difference < 0)
			{
				parent->left = inserted;
			}
			else if (difference > 0)
			{
				parent->right = inserted;
			}
			else
			{
				return false;
			}
		}
		inserted->left = &nil;
		inserted->right = &nil;
		inserted->color = 1;
		TreeNode* fixed = inserted;
		while (fixed != root && fixed->parent->color == 1)
		{
			if (fixed->parent == fixed->parent->parent->left)
			{
				TreeNode* uncle = fixed->parent->parent->right;
				if (uncle->color == 1)
				{
					fixed->parent->color = 0;
					uncle->color = 0;
					fixed->parent->parent->color = 1;
					fixed = fixed->parent->parent;
				}
				else
				{
					if (fixed == fixed->parent->right)
					{
						fixed = fixed->parent;
						RotateLeft(fixed);
					}
					fixed->parent->color = 0;
					fixed->parent->parent->color = 1;
					RotateRight(fixed->parent->parent);
				}
			}
			else
			{
				TreeNode* uncle = fixed->parent->parent->left;
				if (uncle->color == 1)
				{
					fixed->parent->color = 0;
					uncle->color = 0;
					fixed->parent->parent->color = 1;
					fixed = fixed->parent->parent;
				}
				else
				{
					if (fixed == fixed->parent->left)
					{
						fixed = fixed->parent;
						RotateRight(fixed);
					}
					fixed->parent->color = 0;
					fixed->parent->parent->color = 1;
					RotateLeft(fixed->parent->parent);
				}
			}
		}
		root->color = 0;
		return true;
	}

	template<class T> T* TreeHead::FindByIndex(const int* index)
	{
		TreeNode* found = root;
		while (found != &nil)
		{
			T* other = music::ObjectOf<T>(found);
			int difference = *index - other->index;
			if (difference < 0)
			{
				found = found->left;
			}
			else if (difference > 0)
			{
				found = found->right;
			}
			else
			{
				TreeNode* before = Previous(found);
				while (before != 0)
				{
					T* earlier = music::ObjectOf<T>(before);
					if (*index - earlier->index != 0)
					{
						break;
					}
					found = before;
					before = Previous(before);
				}
				return music::ObjectOf<T>(found);
			}
		}
		return 0;
	}
}

namespace om
{
	// FUNCTION: ENGINE 0x105DC230
	template bool TreeHead::InsertByIndex<music::Layer>(music::Layer*);
	// FUNCTION: ENGINE 0x105DC3E0
	template bool TreeHead::InsertByIndex<music::Part>(music::Part*);
	// FUNCTION: ENGINE 0x105DC960
	template music::Part* TreeHead::FindByIndex<music::Part>(const int*);
	// FUNCTION: ENGINE 0x105DC9E0
	template music::Layer* TreeHead::FindByIndex<music::Layer>(const int*);
}

namespace music
{
	// FUNCTION: ENGINE 0x105DC680
	Cell* Cue::GetCellAt(unsigned int part, unsigned int layer)
	{
		return grid.cells[grid.partCount * layer + part];
	}

	// FUNCTION: ENGINE 0x105DC100
	const char* Part::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105DC110
	const char* Layer::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105DCAE0
	// NONMATCHING: the engine keeps this in eax and adds the offset of the node to it, ours takes the node's address with lea (36.4 %)
#ifdef NONMATCHING
	Part::~Part()
	{
		cue->parts.Erase(&node);
	}
#endif

	// FUNCTION: ENGINE 0x105DCB20
	// NONMATCHING: the engine keeps this in eax and adds the offset of the node to it, ours takes the node's address with lea (36.4 %)
#ifdef NONMATCHING
	Layer::~Layer()
	{
		cue->layers.Erase(&node);
	}
#endif

	// FUNCTION: ENGINE 0x105DC6A0
	Cell* Cue::GetCell(unsigned int part, unsigned int layer)
	{
		return grid.cells[grid.partCount * layer + part];
	}


	// FUNCTION: ENGINE 0x105DC1E0
	const char* CellGrid::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105DBF60
	void Layer::SetCellType(om::MetaTypeBase* newCellType)
	{
		cellType = newCellType;
	}

	// The engine's copy is folded with the setters of the cue events' player names (0x105DC640)
	void Part::SetName(const om::ClassName* newName)
	{
		name = *newName;
	}

	// FUNCTION: ENGINE 0x105DCC90
	Part* Cue::GetPart(unsigned int index)
	{
		return parts.FindByIndex<Part>(reinterpret_cast<const int*>(&index));
	}

	// FUNCTION: ENGINE 0x105DCCB0
	Layer* Cue::GetLayer(unsigned int index)
	{
		return layers.FindByIndex<Layer>(reinterpret_cast<const int*>(&index));
	}

	// FUNCTION: ENGINE 0x105DCBF0
	Part* Cue::FindPartByName(const om::ClassName* partName)
	{
		om::TreeNode* node = parts.First();
		Part* part = ObjectOf<Part>(node);
		while (part != 0)
		{
			if (part->name.key == partName->key)
			{
				return part;
			}
			node = parts.Next(&part->node);
			part = ObjectOf<Part>(node);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105DCC40
	Layer* Cue::FindLayerByName(const om::ClassName* layerName)
	{
		om::TreeNode* node = layers.First();
		Layer* layer = ObjectOf<Layer>(node);
		while (layer != 0)
		{
			if (layer->name.key == layerName->key)
			{
				return layer;
			}
			node = layers.Next(&layer->node);
			layer = ObjectOf<Layer>(node);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105DCCD0
	om::String Cue::MakeUniquePartName(om::String baseName)
	{
		om::String result(baseName);
		unsigned int number = 1;
		for (;;)
		{
			om::ClassName key(core::Hash64(result.data == om::gEmptyStringData ? "" : result.data, 0));
			if (FindPartByName(&key) == 0)
			{
				break;
			}
			result = baseName + number;
			++number;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105DCD60
	om::String Cue::MakeUniqueLayerName(om::String baseName)
	{
		om::String result(baseName);
		unsigned int number = 1;
		for (;;)
		{
			om::ClassName key(core::Hash64(result.data == om::gEmptyStringData ? "" : result.data, 0));
			if (FindLayerByName(&key) == 0)
			{
				break;
			}
			result = baseName + number;
			++number;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105DD3E0
	// NONMATCHING: the engine reloads the cue from the part after the stores, ours keeps it in a register (49.4 %)
#ifdef NONMATCHING
	Part::Part(Cue* owner, const om::ClassName* newName, unsigned int newIndex) :
		name(*newName)
	{
		cue = owner;
		index = newIndex;
		unknown18 = 0;
		cue->parts.InsertByIndex(this);
		if (newIndex >= cue->grid.partCount)
		{
			cue->grid.Resize(newIndex + 1, cue->grid.layerCount);
		}
	}
#endif

	// FUNCTION: ENGINE 0x105DD470
	Layer::Layer(Cue* owner, const om::ClassName* newName, unsigned int newIndex) :
		name(*newName),
		index(newIndex),
		cue(owner),
		cellType(0)
	{
		cue->layers.InsertByIndex(this);
		if (newIndex >= cue->grid.layerCount)
		{
			cue->grid.Resize(cue->grid.partCount, newIndex + 1);
		}
	}

	// FUNCTION: ENGINE 0x105DCE50
	// NONMATCHING: the engine steps a pointer through the new cells and keeps the new part count in a register (10.3 %)
#ifdef NONMATCHING
	void CellGrid::Resize(unsigned int newPartCount, unsigned int newLayerCount)
	{
		if (newPartCount == 0 || newLayerCount == 0)
		{
			om::Release(cells, partCount * layerCount * 4, 4);
			cells = 0;
			layerCount = 0;
			partCount = 0;
		}
		else if (newPartCount != partCount || newLayerCount != layerCount)
		{
			unsigned int count = newPartCount * newLayerCount;
			Cell** newCells = static_cast<Cell**>(om::Allocate(AllocationTag(), count * 4, 4));
			for (unsigned int i = 0; i < count; ++i)
			{
				newCells[i] = 0;
			}
			if (cells != 0)
			{
				unsigned int keptParts = om::Min(partCount, newPartCount);
				unsigned int keptLayers = om::Min(layerCount, newLayerCount);
				for (unsigned int part = 0; part < keptParts; ++part)
				{
					for (unsigned int layer = 0; layer < keptLayers; ++layer)
					{
						newCells[layer * newPartCount + part] = cells[layer * partCount + part];
					}
				}
			}
			om::Release(cells, partCount * layerCount * 4, 4);
			partCount = newPartCount;
			layerCount = newLayerCount;
			cells = newCells;
		}
	}
#endif

	// FUNCTION: ENGINE 0x105DD070
	// NONMATCHING: the engine loads the layer count into a register before the allocation size (87.1 %)
#ifdef NONMATCHING
	void CellGrid::InsertPart(unsigned int part)
	{
		unsigned int size = (partCount + 1) * layerCount * 4;
		Cell** newCells = static_cast<Cell**>(om::Allocate(AllocationTag(), size, 4));
		for (unsigned int before = 0; before <= part; ++before)
		{
			for (unsigned int layer = 0; layer < layerCount; ++layer)
			{
				newCells[(partCount + 1) * layer + before] = cells[partCount * layer + before];
			}
		}
		for (unsigned int layer = 0; layer < layerCount; ++layer)
		{
			newCells[(partCount + 1) * layer + part + 1] = 0;
		}
		for (unsigned int after = part + 1; after < partCount; ++after)
		{
			for (unsigned int layer = 0; layer < layerCount; ++layer)
			{
				newCells[(partCount + 1) * layer + after + 1] = cells[partCount * layer + after];
			}
		}
		om::Release(cells, layerCount * partCount * 4, 4);
		partCount = partCount + 1;
		cells = newCells;
	}
#endif

	// FUNCTION: ENGINE 0x105DD160
	// NONMATCHING: register and loop layout (12.2 %)
#ifdef NONMATCHING
	void CellGrid::RemoveLayer(unsigned int layer)
	{
		Cell** newCells = static_cast<Cell**>(om::Allocate(AllocationTag(), (layerCount - 1) * partCount * 4, 4));
		for (unsigned int part = 0; part < partCount; ++part)
		{
			for (unsigned int before = 0; before < layer; ++before)
			{
				newCells[partCount * before + part] = cells[partCount * before + part];
			}
		}
		for (unsigned int part = 0; part < partCount; ++part)
		{
			for (unsigned int after = layer + 1; after < layerCount; ++after)
			{
				newCells[partCount * (after - 1) + part] = cells[partCount * after + part];
			}
		}
		om::Release(cells, partCount * layerCount * 4, 4);
		layerCount = layerCount - 1;
		cells = newCells;
	}
#endif

	// FUNCTION: ENGINE 0x105DD250
	// NONMATCHING: the engine loads both counts into registers for the allocation size (47.3 %)
#ifdef NONMATCHING
	void CellGrid::RemovePart(unsigned int part)
	{
		Cell** newCells = static_cast<Cell**>(om::Allocate(AllocationTag(), (partCount - 1) * layerCount * 4, 4));
		for (unsigned int before = 0; before < part; ++before)
		{
			for (unsigned int layer = 0; layer < layerCount; ++layer)
			{
				newCells[(partCount - 1) * layer + before] = cells[partCount * layer + before];
			}
		}
		for (unsigned int after = part + 1; after < partCount; ++after)
		{
			for (unsigned int layer = 0; layer < layerCount; ++layer)
			{
				newCells[(partCount - 1) * layer + after - 1] = cells[partCount * layer + after];
			}
		}
		om::Release(cells, partCount * layerCount * 4, 4);
		partCount = partCount - 1;
		cells = newCells;
	}
#endif

	template<class T> void DeleteAllOf(om::TreeHead* tree)
	{
		for (;;)
		{
			T* object = ObjectOf<T>(tree->First());
			if (object == 0)
			{
				break;
			}
			delete object;
		}
	}

	// FUNCTION: ENGINE 0x105DC900
	template void DeleteAllOf<Part>(om::TreeHead*);
	// FUNCTION: ENGINE 0x105DC930
	template void DeleteAllOf<Layer>(om::TreeHead*);

	// FUNCTION: ENGINE 0x105DD710
	// NONMATCHING: the engine keeps this in edi and the layer's cell type in ebp, ours the other way round (93.3 %)
#ifdef NONMATCHING
	bool Cue::SetCell(unsigned int part, unsigned int layer, Cell* cell)
	{
		Layer* target = GetLayer(layer);
		if (cell != 0)
		{
			om::MetaTypeBase* current = target->cellType;
			om::MetaTypeBase* playerType = cell->GetPlayerMetaType();
			if (current == 0)
			{
				target->SetCellType(playerType);
			}
			else if (current != playerType)
			{
				return false;
			}
		}
		grid.cells[grid.partCount * layer + part] = cell;
		return true;
	}
#endif

	// FUNCTION: ENGINE 0x105DDCB0
	// NONMATCHING: the engine clears the list words before the loop and scales the cell count with lea (68.3 %)
#ifdef NONMATCHING
	void Cue::Clear()
	{
		unknown54.head = 0;
		unknown54.tail = 0;
		for (unsigned int part = 0; part < grid.partCount; ++part)
		{
			for (unsigned int layer = 0; layer < grid.layerCount; ++layer)
			{
				delete GetCellAt(part, layer);
				SetCell(part, layer, 0);
			}
		}
		om::Release(grid.cells, grid.partCount * grid.layerCount * 4, 4);
		grid.cells = 0;
		grid.layerCount = 0;
		grid.partCount = 0;
		DeleteAllOf<Part>(&parts);
		DeleteAllOf<Layer>(&layers);
	}
#endif

	// FUNCTION: ENGINE 0x105DF800
	// NONMATCHING: the engine multiplies the part count by the layer count, ours the other way round (97.3 %)
#ifdef NONMATCHING
	Cue::~Cue()
	{
		Clear();
	}
#endif

	// FUNCTION: ENGINE 0x105DDF50
	void Cue::RemoveCell(unsigned int part, unsigned int layer)
	{
		Cell* cell = GetCellAt(part, layer);
		if (cell != 0)
		{
			StopCellPlayers(part, layer);
			delete cell;
			SetCell(part, layer, 0);
		}
	}

	// FUNCTION: ENGINE 0x105DDF00
	void Cue::CopyCell(unsigned int fromPart, unsigned int fromLayer, unsigned int toPart, unsigned int toLayer)
	{
		Cell* source = GetCellAt(fromPart, fromLayer);
		if (GetCellAt(toPart, toLayer) == 0 && source != 0)
		{
			SetCell(toPart, toLayer, source->Clone());
		}
	}

	// FUNCTION: ENGINE 0x105DF880
	void Cue::CopyPart(unsigned int toPart, unsigned int fromPart)
	{
		for (unsigned int layer = 0; layer < grid.layerCount; ++layer)
		{
			CopyCell(fromPart, layer, toPart, layer);
		}
	}

	// FUNCTION: ENGINE 0x105DDF90
	void Cue::MoveCell(unsigned int fromPart, unsigned int fromLayer, unsigned int toPart, unsigned int toLayer)
	{
		Cell* source = GetCellAt(fromPart, fromLayer);
		if (GetCellAt(toPart, toLayer) == 0)
		{
			StopCellPlayers(fromPart, fromLayer);
			StopCellPlayers(toPart, toLayer);
			SetCell(toPart, toLayer, source);
			SetCell(fromPart, fromLayer, 0);
		}
	}

	// FUNCTION: ENGINE 0x105DD5B0
	// NONMATCHING: as AddPart: the temporaries of the name are in other frame slots and the registers differ (26.5 %)
#ifdef NONMATCHING
	void Cue::InsertPart(unsigned int index)
	{
		unsigned int before = index;
		index = before + 1;
		Part* part = parts.FindByIndex<Part>(reinterpret_cast<const int*>(&index));
		while (part != 0)
		{
			part->index += 1;
			part = ObjectOf<Part>(parts.Next(&part->node));
		}
		grid.InsertPart(before);
		new Part(this, &om::ClassName(core::Hash64(MakeUniquePartName(om::String(om::String("Part", 0))).GetText(), 0)), index);
	}
#endif

	// FUNCTION: ENGINE 0x105DD770
	// NONMATCHING: the engine builds the name text before the name of the result and keeps the two temporaries in the other frame slots (52 %)
#ifdef NONMATCHING
	void Cue::AddPart()
	{
		unsigned int index = grid.partCount;
		new Part(this, &om::ClassName(core::Hash64(MakeUniquePartName(om::String(om::String("Part", 0))).GetText(), 0)), index);
	}
#endif

	// FUNCTION: ENGINE 0x105DD830
	// NONMATCHING: as AddPart (47.3 %)
#ifdef NONMATCHING
	void Cue::AddLayer()
	{
		unsigned int index = grid.layerCount;
		new Layer(this, &om::ClassName(core::Hash64(MakeUniqueLayerName(om::String("Layer", 0)).GetText(), 0)), index);
	}
#endif

	// FUNCTION: ENGINE 0x105DD500
	Cue::Cue(const om::ClassName& newName) :
		Entity(newName),
		bpm(120.0f),
		timeSignature(4, 4)
	{
	}

	// FUNCTION: ENGINE 0x105DBFF0
	bool Cue::Slot8(void* argument)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x105DD580
	om::EntityTypeBase* Cue::GetEntityType()
	{
		return om::FindEntityType(typeid(Cue));
	}
}
