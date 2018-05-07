#pragma once
#include <DirectXCollision.h>
#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include "..\Engines\Direct2DEngine.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;
using namespace DirectX;

namespace DebugDrawShape
{
	inline void XM_CALLCONV DrawCube(PrimitiveBatch<VertexPositionColor>* batch,
		CXMMATRIX matWorld,
		FXMVECTOR color)
	{
		static const XMVECTORF32 s_verts[8] =
		{
			{ -1.f, -1.f, -1.f, 0.f },
		{ 1.f, -1.f, -1.f, 0.f },
		{ 1.f, -1.f,  1.f, 0.f },
		{ -1.f, -1.f,  1.f, 0.f },
		{ -1.f,  1.f, -1.f, 0.f },
		{ 1.f,  1.f, -1.f, 0.f },
		{ 1.f,  1.f,  1.f, 0.f },
		{ -1.f,  1.f,  1.f, 0.f }
		};

		static const WORD s_indices[] =
		{
			0, 1,
			1, 2,
			2, 3,
			3, 0,
			4, 5,
			5, 6,
			6, 7,
			7, 4,
			0, 4,
			1, 5,
			2, 6,
			3, 7
		};

		VertexPositionColor verts[8];
		for (size_t i = 0; i < 8; ++i)
		{
			XMVECTOR v = XMVector3Transform(s_verts[i], matWorld);
			XMStoreFloat3(&verts[i].position, v);
			XMStoreFloat4(&verts[i].color, color);
		}

		batch->DrawIndexed(D3D11_PRIMITIVE_TOPOLOGY_LINELIST, s_indices, _countof(s_indices), verts, 8);
	}

	inline void XM_CALLCONV DrawRing(PrimitiveBatch<VertexPositionColor>* batch,
		FXMVECTOR origin,
		FXMVECTOR majorAxis,
		FXMVECTOR minorAxis,
		GXMVECTOR color)
	{
		static const size_t c_ringSegments = 32;

		VertexPositionColor verts[c_ringSegments + 1];

		FLOAT fAngleDelta = XM_2PI / float(c_ringSegments);
		// Instead of calling cos/sin for each segment we calculate
		// the sign of the angle delta and then incrementally calculate sin
		// and cosine from then on.
		XMVECTOR cosDelta = XMVectorReplicate(cosf(fAngleDelta));
		XMVECTOR sinDelta = XMVectorReplicate(sinf(fAngleDelta));
		XMVECTOR incrementalSin = XMVectorZero();
		static const XMVECTORF32 s_initialCos =
		{
			1.f, 1.f, 1.f, 1.f
		};
		XMVECTOR incrementalCos = s_initialCos.v;
		for (size_t i = 0; i < c_ringSegments; i++)
		{
			XMVECTOR pos = XMVectorMultiplyAdd(majorAxis, incrementalCos, origin);
			pos = XMVectorMultiplyAdd(minorAxis, incrementalSin, pos);
			XMStoreFloat3(&verts[i].position, pos);
			XMStoreFloat4(&verts[i].color, color);
			// Standard formula to rotate a vector.
			XMVECTOR newCos = incrementalCos * cosDelta - incrementalSin * sinDelta;
			XMVECTOR newSin = incrementalCos * sinDelta + incrementalSin * cosDelta;
			incrementalCos = newCos;
			incrementalSin = newSin;
		}
		verts[c_ringSegments] = verts[0];

		batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP, verts, c_ringSegments + 1);
	}
}

namespace DebugDraw
{
	inline void XM_CALLCONV Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
		const DirectX::BoundingOrientedBox& obb,
		DirectX::FXMVECTOR color = DirectX::Colors::White)
	{
		XMMATRIX matWorld = XMMatrixRotationQuaternion(XMLoadFloat4(&obb.Orientation));
		XMMATRIX matScale = XMMatrixScaling(obb.Extents.x, obb.Extents.y, obb.Extents.z);
		matWorld = XMMatrixMultiply(matScale, matWorld);
		XMVECTOR position = XMLoadFloat3(&obb.Center);
		matWorld.r[3] = XMVectorSelect(matWorld.r[3], position, g_XMSelect1110);

		DebugDrawShape::DrawCube(batch, matWorld, color);
	
	}

	inline void XM_CALLCONV Draw(PrimitiveBatch<VertexPositionColor>* batch,
		const BoundingSphere& sphere,
		FXMVECTOR color)
	{
		XMVECTOR origin = XMLoadFloat3(&sphere.Center);

		const float radius = sphere.Radius;

		XMVECTOR xaxis = g_XMIdentityR0 * radius;
		XMVECTOR yaxis = g_XMIdentityR1 * radius;
		XMVECTOR zaxis = g_XMIdentityR2 * radius;

		DebugDrawShape::DrawRing(batch, origin, xaxis, zaxis, color);
		DebugDrawShape::DrawRing(batch, origin, xaxis, yaxis, color);
		DebugDrawShape::DrawRing(batch, origin, yaxis, zaxis, color);
	}

	inline void XM_CALLCONV Draw(PrimitiveBatch<VertexPositionColor>* batch,
		const BoundingBox& box,
		FXMVECTOR color)
	{
		XMMATRIX matWorld = XMMatrixScaling(box.Extents.x, box.Extents.y, box.Extents.z);
		XMVECTOR position = XMLoadFloat3(&box.Center);
		matWorld.r[3] = XMVectorSelect(matWorld.r[3], position, g_XMSelect1110);

		DebugDrawShape::DrawCube(batch, matWorld, color);
	}
}

namespace DebugInformation2D
{
	inline void cameraPosToScreen(Direct2DEngine * pD2D, Vector3 pos)
	{
		std::wstring info = L"Camera Position:\nX: ";
		info += std::to_wstring(pos.x) + L"\nY: " + std::to_wstring(pos.y) + L"\nZ: " + std::to_wstring(pos.z);
		D2D1_RECT_F rect;
		rect.top = rect.left = 50;
		rect.bottom = rect.right = 400;

		//make a text format
		IDWriteTextFormat * pTextFormat = nullptr;
		HRESULT hr = pD2D->getWriteFactoryPtr()->CreateTextFormat(
			L"Gabriola",
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			32.f,
			L"sv_SV",
			&pTextFormat
		);
		if (FAILED(hr))
			return;
		//make a blue brush
		ID2D1SolidColorBrush * pBrush = nullptr;
		hr = pD2D->getDeviceContextPtr()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f), &pBrush);
		if (SUCCEEDED(hr))
			pD2D->textToScreen(info, pTextFormat, &rect, pBrush);

		//release memory before returning
		if (pTextFormat)
			pTextFormat->Release();
		if (pBrush)
			pBrush->Release();
	}

	inline void FPStoScreen(Direct2DEngine * pD2D, unsigned int hertz)
	{
		std::wstring info = L"FPS: ";
		info += std::to_wstring(hertz);
		D2D1_RECT_F rect;
		rect.top = 320;
		rect.left = 50;
		rect.bottom = 400;
		rect.right = 200;

		//make a text format
		IDWriteTextFormat * pTextFormat = nullptr;
		HRESULT hr = pD2D->getWriteFactoryPtr()->CreateTextFormat(
			L"Gabriola",
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			32.f,
			L"sv_SV",
			&pTextFormat
		);
		if (FAILED(hr))
			return;
		//make a blue brush
		ID2D1SolidColorBrush * pBrush = nullptr;
		hr = pD2D->getDeviceContextPtr()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f), &pBrush);
		if (SUCCEEDED(hr))
			pD2D->textToScreen(info, pTextFormat, &rect, pBrush);

		//release memory before returning
		if (pTextFormat)
			pTextFormat->Release();
		if (pBrush)
			pBrush->Release();
	}
}

#endif // !DEBUGDRAW_H