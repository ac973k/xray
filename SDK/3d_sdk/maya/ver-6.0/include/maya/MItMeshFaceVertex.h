#ifndef _MItMeshFaceVertex
#define _MItMeshFaceVertex
//
//-
// ==========================================================================
// Copyright (C) Alias Systems Corp., and/or its licensors ("Alias").  
// All rights reserved.  These coded instructions, statements, computer  
// programs, and/or related material (collectively, the "Material")
// contain unpublished information proprietary to Alias, which is
// protected by Canadian and US federal copyright law and by international
// treaties. This Material may not be disclosed to third parties, or be copied
// or duplicated, in whole or in part, without the prior written consent of
// Alias.  ALIAS HEREBY DISCLAIMS ALL WARRANTIES RELATING TO THE MATERIAL,
// INCLUDING, WITHOUT LIMITATION, ANY AND ALL EXPRESS OR IMPLIED WARRANTIES OF
// NON-INFRINGEMENT, MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
// IN NO EVENT SHALL ALIAS BE LIABLE FOR ANY DAMAGES WHATSOEVER, WHETHER DIRECT,
// INDIRECT, SPECIAL, OR PUNITIVE, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, OR IN EQUITY, ARISING OUT OF OR RELATED TO THE
// ACCESS TO, USE OF, OR RELIANCE UPON THE MATERIAL.
// ==========================================================================
//+
//
// CLASS:    MItMeshFaceVertex
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MItMeshFaceVertex)
//
//	This class is the iterator for polygonal surfaces - iterates over 
//  face vertices.
//
//	The iterator functions in two modes depending on whether a component
//	is specified. When a component is not given or is NULL the iteration
//	will be over all polygons for the surface.  When a component is given
//	this iterator will iterate over the polygons specified in the component.
//	When iterating over components a DAG path to the surface must also be
//	supplied.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES

#include <maya/MFnDagNode.h>
#include <maya/MObject.h>
#include <maya/MVector.h>
#include <maya/MPoint.h>
#include <maya/MColor.h>
#include <maya/MFloatArray.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MVectorArray.h>
#include <maya/MColorArray.h>
#include <maya/MString.h>

// *****************************************************************************

// DECLARATIONS

class MPointArray;
class MDoubleArray;
class MIntArray;
class MDGModifier;

// *****************************************************************************

// CLASS DECLARATION (MItMeshFaceVertex)

/// Face vertex iterator
/**
  Iterate over face vertices of polygonal surfaces
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYA_EXPORT MItMeshFaceVertex
{
public:
	///
    MItMeshFaceVertex( const MObject & polyObject, MStatus * ReturnStatus = NULL );
    ///
    MItMeshFaceVertex( const MDagPath &polyObject,
					MObject & component = MObject::kNullObj,
					MStatus * ReturnStatus = NULL );
	///
	virtual ~MItMeshFaceVertex();
    ///
    bool        isDone( MStatus * ReturnStatus = NULL );
    ///
    MStatus     next();
    ///
    MStatus     reset();
    ///
    MStatus     reset( const MObject & polyObject );
    ///
    MStatus     reset( const MDagPath &polyObject,
						MObject & component = MObject::kNullObj );
    ///
    int         vertId( MStatus * ReturnStatus = NULL ) const;
	///	
    int         faceId( MStatus * ReturnStatus = NULL ) const;
    ///
    int         faceVertId( MStatus * ReturnStatus = NULL ) const;

    ///
    MPoint      position( MSpace::Space space = MSpace::kObject,
						  MStatus * ReturnStatus = NULL );

    /// Get/Set methods for normals.
    MStatus     getNormal( MVector & normal,
						   MSpace::Space space = MSpace::kObject );
	/// 
    int         normalId( MStatus * ReturnStatus = NULL );


	// UV methods. Mention sharing in docs when setUVs
	///
	bool		hasUVs( MStatus * ReturnStatus = NULL ) const;
    /// 
    bool        hasUVs( const MString & uvSet,
						MStatus * ReturnStatus = NULL ) const;
    /// 
    MStatus     getUV( float2 & uvPoint, const MString * uvSet = NULL) const;
    ///
    MStatus     getUVIndex( int & index, const MString *uvSet = NULL );
    ///
    MStatus     getUVIndex( int & index, float & u, float & v,
							const MString *uvSet = NULL);

	// Color methods. Mention sharing in docs when setUVs
	///
	bool		hasColor(MStatus * ReturnStatus = NULL ) const;
	///
	MStatus		getColor(MColor &color);
	/// 		
	MStatus		getColorIndex( int & index );


    ///
    MStatus     updateSurface();
    ///
    MStatus     geomChanged();
	///
	MStatus		setIndex(int faceId, int vertFaceId, 
					     int &prevFaceId, int &prevVertId );

protected:
    bool		getUVSetIndex( const MString * uvSetName,
							   int & uvSet) const;

private:

    static const char*  className();
    MPtrBase *      f_shape;
    void 	 *      f_path;
    void 	 *      f_geom;
	void	 *		f_ref;

	void	 *		fCompIter;		// face component iterator
	void     *      fElements;		// pointer to the face component list

	int				fCurrFaceId; 	
	int				fCurrOffset; 
	int				fCurrVertOff;
	int             fNumbFaceVerts;	// number of all face vertices
};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MItMeshFaceVertex */
