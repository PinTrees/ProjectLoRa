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

	// 시작 위치와 끝 위치의 유효성 검사 및 충돌 맵(m_fiieldCollision)의 유효성 검사
	if ((_sX < 0 || _sX >= m_GridWidth) ||
		(_sY < 0 || _sY >= m_GridHeight) ||
		(_sX == _eX && _sY == _eY) ||
		(m_fiieldCollision == nullptr))
	{
		return false; // 검색 실패
	}

	//===================================================================
	// INITILIZE SETTING
	//===================================================================

	// 끝 위치를 설정
	m_EndPos.m_x = _eX;
	m_EndPos.m_y = _eY;

	// 검색 결과를 담을 리스트를 비움
	mResultNodes.clear();

	// 오픈 리스트, 클로즈드 리스트, 노드 컨테이너를 초기화하여 검색 준비
	m_OpenList.Clear();
	m_Searched.Clear();

	// 시작 노드를 생성하고 초기화
	auto spStartNode = std::make_shared<JPSNode>();
	if (!spStartNode)
		throw std::bad_alloc();
	spStartNode->Set(nullptr, JPSCoord(_sX, _sY), m_EndPos, 8);


	//================================================
	// START
	//================================================

	// 시작 노드를 오픈 리스트에 삽입
	// 시작 노드를 이미 탐색한 것으로 표시
	m_OpenList.InsertNewone(spStartNode);
	m_Searched.SetAt(spStartNode->m_Pos.m_x, spStartNode->m_Pos.m_y, true);


	//===================================================================
	// LOOP
	//===================================================================

	// 오픈 리스트가 비어있을 때까지 반복하여 검색
	while (m_OpenList.Count())
	{
		// 현재 노드를 오픈 리스트에서 꺼냄
		auto  spCurrNode = m_OpenList.PopMax();
		// 현재 노드의 이웃 방향들을 계산하여 더할 비트 마스크를 구함
		Int32 Directions = _ForcedNeighbours(spCurrNode->m_Pos, spCurrNode->m_CardinalDir) | _NaturalNeighbours(spCurrNode->m_CardinalDir);

		// 현재 노드의 이웃 노드들에 대해 반복하여 탐색
		for (Int32 dir = 0; dir < 8; dir++)
		{
			// 비트 마스크를 이용하여 현재 방향이 유효한지 확인
			if ((1 << dir) & Directions)
			{
				// 새로운 노드의 좌표를 계산
				auto CoordinateNewC = _JumpNew(spCurrNode->m_Pos, dir);

				// 새로운 노드의 좌표가 유효하다면 계속 진행
				if (!CoordinateNewC.IsEmpty())
				{
					//================================================
					// ARRIVED 목표 지점에 도달한 경우
					//================================================
					if (CoordinateNewC == m_EndPos)
					{
						// 목표 지점을 결과 리스트의 첫 번째로 추가
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
						return true; // 검색 성공
					}

					//====================================================
					// KEEP SEARCH: 계속 탐색해야하는 경우
					//====================================================

					// 새로운 노드를 생성하고 초기화
					auto newNode = std::make_shared<JPSNode>();
					if (!newNode)
						throw std::bad_alloc();
					newNode->Set(spCurrNode, CoordinateNewC, m_EndPos, dir);

					//================================================

					// 새로운 노드가 이미 탐색되지 않은 노드라면 오픈 리스트에 삽입
					if (!m_Searched.IsSet(CoordinateNewC.m_x, CoordinateNewC.m_y))
					{
						m_OpenList.InsertNewone(newNode);
						m_Searched.SetAt(CoordinateNewC.m_x, CoordinateNewC.m_y, true);
					}
					else // 이미 탐색된 노드라면 오픈 리스트에 더 작은 비용으로 삽입
					{
						m_OpenList.InsertSmaller(newNode);
					}
				}
			}
		}
	}

	// 모든 노드 탐색됨
	return false; // 검색 실패
}


