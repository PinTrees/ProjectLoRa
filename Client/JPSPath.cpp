#include "pch.h"
#include "JPSPath.h"
#include "JPSHeap.h"

//--------------------------------------------------------------------
// Class: Search()
// Desc	: 
//--------------------------------------------------------------------
bool JPSPath::Search(Int32 _sX, Int32 _sY, Int32 _eX, Int32 _eY, std::list<JPSCoord>& mResultNodes)
{
	//===================================================================
	// CHECK
	//===================================================================

	// ���� ��ġ�� �� ��ġ�� ��ȿ�� �˻� �� �浹 ��(m_fiieldCollision)�� ��ȿ�� �˻�
	if ((_sX < 0 || _sX >= m_GridWidth) ||
		(_sY < 0 || _sY >= m_GridHeight) ||
		(_sX == _eX && _sY == _eY) ||
		(m_fiieldCollision == nullptr))
	{
		return false; // �˻� ����
	}

	//===================================================================
	// INITILIZE SETTING
	//===================================================================

	// �� ��ġ�� ����
	m_EndPos.m_x = _eX;
	m_EndPos.m_y = _eY;

	// �˻� ����� ���� ����Ʈ�� ���
	mResultNodes.clear();

	// ���� ����Ʈ, Ŭ����� ����Ʈ, ��� �����̳ʸ� �ʱ�ȭ�Ͽ� �˻� �غ�
	m_OpenList.Clear();
	m_Searched.Clear();

	// ���� ��带 �����ϰ� �ʱ�ȭ
	auto spStartNode = std::make_shared<JPSNode>();
	if (!spStartNode)
		throw std::bad_alloc();
	spStartNode->Set(nullptr, JPSCoord(_sX, _sY), m_EndPos, 8);


	//================================================
	// START
	//================================================

	// ���� ��带 ���� ����Ʈ�� ����
	// ���� ��带 �̹� Ž���� ������ ǥ��
	m_OpenList.InsertNewone(spStartNode);
	m_Searched.SetAt(spStartNode->m_Pos.m_x, spStartNode->m_Pos.m_y, true);


	//===================================================================
	// LOOP
	//===================================================================

	// ���� ����Ʈ�� ������� ������ �ݺ��Ͽ� �˻�
	while (m_OpenList.Count())
	{
		// ���� ��带 ���� ����Ʈ���� ����
		auto  spCurrNode = m_OpenList.PopMax();
		// ���� ����� �̿� ������� ����Ͽ� ���� ��Ʈ ����ũ�� ����
		Int32 Directions = _ForcedNeighbours(spCurrNode->m_Pos, spCurrNode->m_CardinalDir) | _NaturalNeighbours(spCurrNode->m_CardinalDir);

		// ���� ����� �̿� ���鿡 ���� �ݺ��Ͽ� Ž��
		for (Int32 dir = 0; dir < 8; dir++)
		{
			// ��Ʈ ����ũ�� �̿��Ͽ� ���� ������ ��ȿ���� Ȯ��
			if ((1 << dir) & Directions)
			{
				// ���ο� ����� ��ǥ�� ���
				auto CoordinateNewC = _JumpNew(spCurrNode->m_Pos, dir);

				// ���ο� ����� ��ǥ�� ��ȿ�ϴٸ� ��� ����
				if (!CoordinateNewC.IsEmpty())
				{
					//================================================
					// ARRIVED ��ǥ ������ ������ ���
					//================================================
					if (CoordinateNewC == m_EndPos)
					{
						// ��ǥ ������ ��� ����Ʈ�� ù ��°�� �߰�
						mResultNodes.push_front(m_EndPos);

						// RECURSIVE TO START POINT
						auto  spTraceNode = spCurrNode;
						Int32 CurDir = _GetCoordinateDir(m_EndPos, spCurrNode->m_Pos);
						while (spTraceNode)
						{
							Int32 NextDir = 0;
							if (spTraceNode->m_spParent)	NextDir = _GetCoordinateDir(spTraceNode->m_Pos, spTraceNode->m_spParent->m_Pos);
							if (CurDir != NextDir)			mResultNodes.push_front(spTraceNode->m_Pos);
							spTraceNode = spTraceNode->m_spParent;
							CurDir = NextDir;
						}
						return true; // �˻� ����
					}

					//====================================================
					// KEEP SEARCH: ��� Ž���ؾ��ϴ� ���
					//====================================================

					// ���ο� ��带 �����ϰ� �ʱ�ȭ
					auto newNode = std::make_shared<JPSNode>();
					if (!newNode)
						throw std::bad_alloc();
					newNode->Set(spCurrNode, CoordinateNewC, m_EndPos, dir);

					//================================================

					// ���ο� ��尡 �̹� Ž������ ���� ����� ���� ����Ʈ�� ����
					if (!m_Searched.IsSet(CoordinateNewC.m_x, CoordinateNewC.m_y))
					{
						m_OpenList.InsertNewone(newNode);
						m_Searched.SetAt(CoordinateNewC.m_x, CoordinateNewC.m_y, true);
					}
					else // �̹� Ž���� ����� ���� ����Ʈ�� �� ���� ������� ����
					{
						m_OpenList.InsertSmaller(newNode);
					}
				}
			}
		}
	}

	// ��� ��� Ž����
	return false; // �˻� ����
}


