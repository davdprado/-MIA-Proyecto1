import { ComponentFixture, TestBed } from '@angular/core/testing';

import { EditpermisosComponent } from './editpermisos.component';

describe('EditpermisosComponent', () => {
  let component: EditpermisosComponent;
  let fixture: ComponentFixture<EditpermisosComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ EditpermisosComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(EditpermisosComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
