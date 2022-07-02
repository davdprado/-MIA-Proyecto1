import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ClientpanelComponent } from './clientpanel.component';

describe('ClientpanelComponent', () => {
  let component: ClientpanelComponent;
  let fixture: ComponentFixture<ClientpanelComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ClientpanelComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(ClientpanelComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
